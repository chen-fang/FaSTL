#pragma once

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

/* Notations:
 * __USER_CHUNK_SIZE - chunk size selected by the user
 * chunk_size - adjusted chunk size based on __USER_CHUNK_SIZE
 * mb - memory block
 * chunk - memory chunk
 * n - number
 * sz/size - size in bytes
 */

template< typename T >
void print ( T content )
{
   std::cout << content << std::endl;
}

template< typename T1, typename T2 >
void print ( T1 c1, T2 c2 )
{
   std::cout << c1 << "\t" << c2 << std::endl;
}

namespace fastl
{
   template< typename __ALLOC = fastl :: malloc_alloc<> >
   class Manager // single instance
   {
   public:
      void initialize()
      {
	 p_entry = nullptr;
	 N = 0;
      }

      void update( std::size_t _sz )
      {
	 std::size_t n = std::log2( _sz );
	 if( n > N )
	 {
	    void* p_dealloc = p_entry;
	    p_entry = __ALLOC :: allocate( n * sizeof(void*) );

	    std::size_t i = 0;
	    for( ; i < N; ++i )
	    {
	       p_entry[i] = p_dealloc[i];
	    }
	    for( ; i < n; ++i )
	    {
	       p_entry[i] = nullptr;
	    }

	    N = n;
	    __ALLOC :: deallocate( p_dealloc );

#ifdef DUMP_POOL
	    std::cout << "Manager updated:" << std::endl;
#endif
	 }
      }

      void* operator[] ( std::size_t i )         { return p_entry[i]; }
      void* operator[] ( std::size_t i ) const   { return p_entry[i]; }

      void*& nextof( void* _p )
      {
	 return *(static_cast<void**>( _p ));
      }

   private:
      Manager() { /* ctor is disabled */ }

   private:	       
      void* p_entry;
      std::size_t N;
   };


// ==========================================================================
// ==========================================================================
// ==========================================================================
   template< typename __USER_CHUNK_SIZE = 0,
	     typename __ALLOC = fastl :: malloc_alloc<> >
   class pool : public __ALLOC
   {
   public:
//       pool ( std::size_t _init_n_chunk )
// 	 : GrowNum(_init_n_chunk), MemBlock_List(nullptr), p_available(nullptr)
//       {
// 	 static_assert( __USER_CHUNK_SIZE > 0,
// 			"freelist_pool :: __USER_CHUNK_SIZE <=0 !!!" );

// 	 chunk_size = alloc_size();
// 	 expand(_init_n_chunk);
//       }

//       freelist_pool ( std::size_t _init_n_chunk, std::size_t _grow_n_chunk )
// 	 : GrowNum(_grow_n_chunk), MemBlock_List(nullptr), p_available(nullptr)
//       {
// #ifdef DUMP_FREELIST
// 	 std::cout << "freelist()" << std::endl;
// #endif
// 	 static_assert( __USER_CHUNK_SIZE > 0,
// 			"freelist_pool :: __USER_CHUNK_SIZE <= 0 !!!" );

// 	 chunk_size = alloc_size();
// 	 expand( _init_n_chunk );
//       }

      pool ( std::size_t _init_size )
	 : GrowSZ(_init_size), MemBlock_List(nullptr),
	   p_availabe_pool(nullptr), remaining_buffer_size(0)
      {
#ifdef DUMP_POOL
	 std::cout << "pool()" << std::endl;
#endif
	 M.initialize();
	 expand( _init_size );

      }

      ~pool()
      {
	 void* p_destroy = MemBlock_List;
	 while( p_destroy != nullptr )
	 {
	    MemBlock_List = nextof( MemBlock_List );

#ifdef DUMP_FREELIST
	    std::cout << "=================== destruct--------------: " << p_destroy << std::endl;
#endif

	    __ALLOC :: deallocate( p_destroy );
	    p_destroy = MemBlock_List;
	 }
	 __ALLOC :: deallocate( p_available_recycle );
      }

      /*
       * Allocate one chunk from the pool.
       * If no chunk is available, expand the pool and allocate.
       */
      void* allocate ( std::size_t _alloc_size )
      {
	 std::size_t P = std::log2(_alloc_size);
	 if( p_available_pool == nullptr && M[P] == nullptr )
	 {
#ifdef DUMP_POOL
	    std::cout << "!!! Not enouth space: expand !!!" << std::endl;
#endif
	    
	    expand( GrowNum );
	 }

	 void* p_ret;
	 if( remaining_memory_size >= _alloc_size )
	 {
	    p_ret = p_available_pool;
	    remaining_memory_size -= _alloc_size;
	 }
	 else
	 {
	    p_ret = M[P];
	    M[P] = Manager.nextof( M[P] );
	 }
	 
#ifdef DUMP_POOL
	 std::cout << "### allocate:\t" << p_ret << std::endl;
	 std::cout << "### next:\t" << p_available << std::endl << std::endl;
#endif
	 return p_ret;
      }


      void deallocate( void* _p_dealloc )
      {
	 if( _p_dealloc != nullptr )
	 {
	    std::size_t P = std::log2( _p_dealloc );
	    void* p_second = M[P];
	    M[P] = _p_dealloc;
	    nextof( M[P] ) = p_second;

#ifdef DUMP_FREELIST
	    std::cout <<"### deallocate:\t" << _p_dealloc << std::endl;
	    std::cout <<"### next:\t" << p_second << std::endl << std::endl;
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
	    M.update( _mb_sz );
	    Add_MemBlock( p_mb_head );
	 }
	 
#ifdef DUMP_FREELIST
	 std::cout << "--------------- expand -------------------" << std::endl;
	 std::cout << "MemBlock_size = " << mb_sz << std::endl;
	 std::cout << "MemBlock:   " << p_mb_head << " --- --- > "
		   << (void*)( (char*)p_mb_head + mb_sz ) << std::endl;

	 std::cout << "Buffer:     " << p_available << " --- --- > "
		   << (void*)( (char*)p_available + _num_chunk * chunk_size ) << std::endl;

	 std::cout << "------------------------------------------" << std::endl;
#endif
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


   private:
      //std::size_t InitNum;
      std::size_t GrowSZ;
      void*       MemBlock_List;
      void*       p_available_pool;
      std::size_t remaining_memory_size;
      Manager     M;
      //std::size_t chunk_size;
   };
}
