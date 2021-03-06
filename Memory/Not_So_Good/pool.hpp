#pragma once

#define STD_SIZEOF_SIZE_T     sizeof(std::size_t)
#define STD_SIZEOF_POINTER    sizeof(void*)

// created by: Chen Fang
// 02/14/2016

/* 
 * Level 2 
 * Memory pool based on freelist.
 * Pros:
 *    1) fast allocation
 *    2) fast deallocation
 *    3) recyclable
 * Cons:
 *    1) pool size cannot be decreased
 *    2) fix-sized chunks
 *
 * Application:
 * Good for:
 *    - list
 *    - chunk size is known at compile time
 *    - single object allocation
 * Bad for:
 *    - vector (size unknown until runtime)
 */


#include "malloc_alloc.hpp"
#include <cmath>

/* Notations:
 * __USER_CHUNK_SIZE - chunk size selected by the user
 * chunk_size - adjusted chunk size based on __USER_CHUNK_SIZE
 * mb - memory block
 * chunk - memory chunk
 * n - number
 * sz/size - size in bytes
 */

// // template< typename T >
// void print ( T content )
// {
//    std::cout << content << std::endl;
// }

// template< typename T1, typename T2 >
// void print ( T1 c1, T2 c2 )
// {
//    std::cout << c1 << "\t" << c2 << std::endl;
// }

namespace fastl
{
   template< typename __ALLOC = fastl :: malloc_alloc<> >
   class RecycleManager : public __ALLOC
   {
   public:
      void initialize()
      {
	 p_entry = nullptr;
	 p_entry_char = nullptr;
	 n_entry = 0;
      }

      void update( std::size_t _sz )
      {
	 std::size_t N = std::log2( _sz );
	 if( N > n_entry  )
	 {
#ifdef DUMP_POOL
	    std::cout << "------ Recycle Manager Updated ------"<< std::endl;
	    std::cout << "Before update:" << std::endl;
	    print();
#endif
	    void** p_dealloc = p_entry;
	    char** p_dealloc_char = static_cast<char**>( static_cast<void*>(p_dealloc) );
	    
	    p_entry = static_cast<void**>( __ALLOC :: allocate( N * STD_SIZEOF_POINTER ) );
	    p_entry_char = static_cast<char**>( static_cast<void*>(p_entry) );

	    std::size_t i = 0;
	    for( ; i < n_entry; ++i )
	    {
	       p_entry_char[i] = p_dealloc_char[i];
	    }
	    for( ; i < N; ++i )
	    {
	       p_entry_char[i] = nullptr;
	    }

	    n_entry = N;
	    __ALLOC :: deallocate( p_dealloc );

#ifdef DUMP_POOL
	    std::cout << "After update:" << std::endl;
	    print();
#endif
	 }
      }

      void print()
      {
	 std::cout << "### Recycle Manager Size:  " << n_entry << std::endl;
	 std::cout << "### Recycle Manager Entry: " << p_entry << std::endl;
	 for( std::size_t i = 0 ; i < n_entry; ++i )
	 {
	    void* p_run = static_cast<void*>( p_entry_char[i] );
	    std::cout << "### " << i << " --- " << p_run;
	    while( p_run != nullptr )
	    {
	       p_run = this->nextof( p_run );
	       std::cout << " --- " << p_run;
	    }
	    std::cout << std::endl;
	 }
	 std::cout << std::endl;
      }	    

      void*& operator[] ( std::size_t i )
      {
	 return *static_cast<void**>( static_cast<void*>( p_entry_char + i ) );
      }

      void*& operator[] ( std::size_t i ) const
      {
	 return *static_cast<void**>( static_cast<void*>( p_entry_char + i ) );
      }

      void*& nextof( void* _p )
      {
	 return *(static_cast<void**>( _p ));
      }

      std::size_t size()
      {
	 return n_entry;
      }

   public:
      //private:
      RecycleManager()  { /* ctor is disabled */ }
      ~RecycleManager()
      {
#ifdef DUMP_POOL
	 std::cout << "~RecycleManager: " << (void*)p_entry << std::endl;
#endif
	 __ALLOC :: deallocate( static_cast<void*>(p_entry) );
      }


   private:	       
      void**      p_entry;
      char**      p_entry_char;
      std::size_t n_entry;
   };
      



// ==========================================================================
// ==========================================================================
// ==========================================================================
// < __UNIFORM_INTERFACE_TAG > is set to provide uniform interface w.r.t.
// freelist_pool, which requres the chunk size

   template< std::size_t __UNIFORM_INTERFACE_TAG = 0,
	     typename __ALLOC = fastl :: malloc_alloc<> >
   class Pool : public __ALLOC
   {
   public:
      typedef std::size_t size_type;
      
      Pool ( std::size_t _init_size )
	 : GrowSZ(_init_size), MemBlock_List(nullptr),
	   p_available_pool(nullptr), remaining_memory_size(0)
      {
#ifdef DUMP_POOL
	 std::cout << "pool( _init_size )" << std::endl;
#endif
	 recycle.initialize();
	 expand( _init_size );
      }

      Pool ( std::size_t _init_size, std::size_t _grow_size )
	 : GrowSZ(_grow_size), MemBlock_List(nullptr),
	   p_available_pool(nullptr), remaining_memory_size(0)
      {
	 recycle.initialize();
	 expand( _init_size );
      }

      ~Pool()
      {
	 void* p_destroy = MemBlock_List;
	 while( p_destroy != nullptr )
	 {
	    MemBlock_List = nextof( MemBlock_List );

#ifdef DUMP_POOL
	    std::cout << "=================== destruct--------------: " << p_destroy << std::endl;
#endif

	    __ALLOC :: deallocate( p_destroy );
	    p_destroy = MemBlock_List;
	 }
      }

      /*
       * Allocate one chunk from the pool.
       * If no chunk is available, expand the pool and allocate.
       */


      void* allocate ( std::size_t _alloc_size )
      {

	 std::size_t buffer_sz = AllocSize( _alloc_size );
	 std::size_t P = std::log2( buffer_sz );
	 std::size_t request_sz = buffer_sz + STD_SIZEOF_SIZE_T + STD_SIZEOF_POINTER;

	 void* p_alloc_head;

	 if( remaining_memory_size >= request_sz )
	 {
	    p_alloc_head = allocate_from_pool( request_sz );
	 }
	 

	 else if( (P+1) <= recycle.size() && recycle[P] != nullptr )
	 {
	    p_alloc_head = allocate_from_recycle( P );
	 }

	 else
	 {
#ifdef DUMP_POOL
	    std::cout << "!!! Not enouth space: expand !!!" << std::endl;
#endif
	    bool is_successful = expand( GrowSZ );
	    if( is_successful == true )
	    {
	       GrowSZ *= 2;
	       p_alloc_head = allocate( _alloc_size );
	    }
	    else
	    {
	       p_alloc_head = nullptr; /* other strategies may apply */
	    }
	 }
	 
	 void* pSize = Determine_pSize( p_alloc_head );
	 *static_cast<size_type*>(pSize) = buffer_sz;
	 return Determine_pBegin( p_alloc_head );	
      }


      void deallocate( void* _p_dealloc )
      {
	 if( _p_dealloc != nullptr )
	 {
	    void* p_head_dealloc = Recover_pHead( _p_dealloc );
	    std::size_t P = std::log2( *static_cast<size_type*>( Recover_pSize(_p_dealloc)) );
	    void* p_second = recycle[P];
	    recycle[P] = p_head_dealloc;
	    nextof( recycle[P] ) = p_second;

#ifdef DUMP_POOL
	    std::cout <<"deallocate:" << std::endl;
	    std::cout <<"*** deallocate:\t" << Recover_pHead(_p_dealloc) << std::endl;
	    std::cout <<"*** next:\t" << p_second << std::endl << std::endl;
	    recycle.print();
#endif

	    _p_dealloc = nullptr;
	 }
      }


   private:
      bool expand ( std::size_t _mb_sz )
      {
	 bool is_successful = false;
	 std::size_t mb_sz = header_size() + _mb_sz;
	 void* p_mb_head = __ALLOC :: allocate( mb_sz );
	 if( p_mb_head != nullptr )
	 {
	    is_successful = true;
	    p_available_pool = static_cast<void*>( static_cast<char*>(p_mb_head) + header_size() );
	    remaining_memory_size = _mb_sz;
	    recycle.update( _mb_sz );
	    Add_MemBlock( p_mb_head );
	 }
	 
#ifdef DUMP_POOL
	 std::cout << "--------------- expand -------------------" << std::endl;
	 std::cout << "MemBlock_size = " << mb_sz << std::endl;
	 std::cout << "MemBlock:   " << p_mb_head << " --- --- > "
		   << (void*)( (char*)p_mb_head + mb_sz ) << std::endl;

	 std::cout << "Buffer:     " << p_available_pool << " --- --- > "
		   << (void*)( (char*)p_available_pool + _mb_sz ) << std::endl;

	 std::cout << "------------------------------------------" << std::endl;
#endif
	 return is_successful;
      }

      void Add_MemBlock( void* _p_new_mb )
      {
	 if( _p_new_mb != nullptr )
	 {
	    void* p_old = MemBlock_List;
	    MemBlock_List = _p_new_mb;
	    nextof( MemBlock_List ) = p_old;
	 }
      }


      static void*& nextof( void* _p )
      {
	 return *(static_cast<void**>( _p ));
      }

      std::size_t header_size ()
      {
	 return sizeof( MemBlock_List );
      }

      std::size_t AllocSize ( std::size_t _alloc_sz )
      {
	 std::size_t ret_sz;

	 if( _alloc_sz < 16 )
	 {
	    ret_sz = 16;
	 }
	 else
	 {
	    int N = std::log2( _alloc_sz - 1 );
	    ret_sz = 1 << (N+1);
	 }
	 return ret_sz;
      }

      
      /*
       * functions for buffer information
       */
      void* Recover_pHead ( void* _p_begin )
      {
	 return static_cast<void*>( static_cast<char*>(_p_begin) -
				    STD_SIZEOF_SIZE_T - STD_SIZEOF_POINTER  );
      }

      void* Recover_pSize ( void* _p_begin )
      {
	 return static_cast<void*>( static_cast<char*>(_p_begin) - STD_SIZEOF_SIZE_T );
      }

      void* Determine_pNext ( void* _p_head )
      {
	 return _p_head;
      }

      void* Determine_pSize ( void* _p_head )
      {
	 return static_cast<void*>( static_cast<char*>(_p_head) + STD_SIZEOF_POINTER );
      }

      void* Determine_pBegin ( void* _p_head )
      {
	 return static_cast<void*>( static_cast<char*>(_p_head) +
				    STD_SIZEOF_POINTER + STD_SIZEOF_SIZE_T );
      }

      /* 
       * Auxillary Functions
       */
      void* allocate_from_pool ( std::size_t _request_sz )
      {
#ifdef DUMP_POOL
	 std::cout << "-------- allocate from pool ----------" << std::endl;
#endif

	 void* p_alloc_head;
	 p_alloc_head = p_available_pool;
	 p_available_pool = static_cast<char*>(static_cast<char*>(p_available_pool) + _request_sz);
	 remaining_memory_size -= _request_sz;
	    
#ifdef DUMP_POOL
	 std::cout << "### request_sz:\t" << _request_sz << std::endl;
	 std::cout << "### p_alloc_head:\t" << p_alloc_head << std::endl;
	 std::cout << "### p_availale_pool:\t" << p_available_pool << std::endl;
	 std::cout << "--------------------------------------" << std::endl;
#endif
	 return p_alloc_head;
      }

      void* allocate_from_recycle ( std::size_t _P )
      {
#ifdef DUMP_POOL
	 std::cout << "-------- allocate from recycle ----------" << std::endl;
#endif

	 void* p_alloc_head;
	 p_alloc_head = recycle[_P];
	 recycle[_P] = recycle.nextof( recycle[_P] );

#ifdef DUMP_POOL
	 std::cout << "### p_alloc_head:\t" << p_alloc_head << std::endl;
	 std::cout << "recycle info:" << std::endl;
	 recycle.print();
	 std::cout << "-----------------------------------------" << std::endl;
#endif	    	    

	 return p_alloc_head;
      }

   private:
      std::size_t       GrowSZ;
      void*             MemBlock_List;
      void*             p_available_pool;
      std::size_t       remaining_memory_size;

      typedef fastl::RecycleManager<> RecycleManager;
      RecycleManager     recycle;
   };
}
