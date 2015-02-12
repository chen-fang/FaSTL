#pragma once

/* 
 * Level 2 
 * Memory pool built on coherent_freelist.
 */


#include "../level_1/malloc_alloc.hpp"

//#include "../helper/helper.h"
//#include "../policy/policy.h"
//#include "../level_1/coherent_freelist.hpp"

/* Notations:
 * __USER_CHUNK_SIZE - chunk size selected by the user
 * chunk_size - adjusted chunk size based on __USER_CHUNK_SIZE
 * mb - memory block
 * chunk - memory chunk
 *
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
   template< std::size_t __USER_CHUNK_SIZE,
	     typename __Alloc = fastl :: malloc_alloc >
   class freelist_pool : public __Alloc
   {
   public:
      freelist_pool ( std::size_t _init_n_chunk )
	 : GrowNum(_init_n_chunk), MemBlock_List(nullptr), p_available(nullptr)
      {
	 static_assert( __USER_CHUNK_SIZE > 0,
			"freelist_pool :: __USER_CHUNK_SIZE <=0 !!!" );

	 chunk_size = alloc_size();
	 expand(_init_n_chunk);
      }

      freelist_pool ( std::size_t _init_n_chunk, std::size_t _grow_n_chunk )
	 : GrowNum(_grow_n_chunk), MemBlock_List(nullptr), p_available(nullptr)
      {
#ifdef DUMP_FREELIST
	 std::cout << "freelist()" << std::endl;
#endif
	 static_assert( __USER_CHUNK_SIZE > 0,
			"freelist_pool :: __USER_CHUNK_SIZE <= 0 !!!" );

	 chunk_size = alloc_size();
	 expand( _init_n_chunk );
      }

      ~freelist_pool()
      {
	 void* p_destroy = MemBlock_List;
	 while( p_destroy != nullptr )
	 {
	    MemBlock_List = nextof( MemBlock_List );

#ifdef DUMP_FREELIST
	    std::cout << "=================== destruct--------------: " << p_destroy << std::endl;
#endif

	    __Alloc :: deallocate( p_destroy );
	    p_destroy = MemBlock_List;
	 }
      }

      void* allocate ()
      {
	 if( p_available == nullptr )
	 {
#ifdef DUMP_FREELIST
	    std::cout << "!!! Not enouth space: expand !!!" << std::endl;
#endif
	    
	    expand( GrowNum );
	 }

	 void* p_ret = p_available;
	 p_available = nextof( p_available );
	 
#ifdef DUMP_FREELIST
	 std::cout << "### allocate:\t" << p_ret << std::endl;
	 std::cout << "### next:\t" << p_available << std::endl << std::endl;
#endif
	 return p_ret;
      }

      void deallocate( void* _p_dealloc )
      {
	 if( _p_dealloc != nullptr )
	 {
	    void* p_second = p_available;
	    p_available = _p_dealloc;
	    nextof( p_available ) = p_second;

#ifdef DUMP_FREELIST
	    std::cout <<"### deallocate:\t" << _p_dealloc << std::endl;
	    std::cout <<"### next:\t" << p_second << std::endl << std::endl;
#endif
	 }
      }


   private:
      void expand ( std::size_t _num_chunk )
      {
	 std::size_t mb_sz = header_size() + _num_chunk * chunk_size;
	 void* p_mb_head = __Alloc :: allocate( mb_sz );
	 p_available = static_cast<void*>( static_cast<char*>(p_mb_head) + header_size() );

	 Add_MemBlock( p_mb_head );
	 segregate( _num_chunk );
	 
#ifdef DUMP_FREELIST
	 std::cout << "--------------- expand -------------------" << std::endl;
	 std::cout << "chunk_size = " << chunk_size << std::endl;
	 std::cout << "num_chunks = " << _num_chunk << std::endl;
	 std::cout << "MemBlock_size = " << mb_sz << std::endl;
	 std::cout << "MemBlock:   " << p_mb_head << " --- --- > " << p_mb_head + mb_sz << std::endl;
	 std::cout << "Buffer:     " << p_available << " --- --- > "
		   << p_available + _num_chunk * chunk_size << std::endl;
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

      void segregate( std::size_t num_chunk )
      {
	 /*  chunk_num  - total number of chunks to be segregated */

	 void* p_run = p_available;
	 for( std::size_t i = 1; i < num_chunk; ++i )
	 {
	    void* test = static_cast<void*>( static_cast<char*>( p_run ) + chunk_size );
	    nextof( p_run ) = static_cast<void*>( static_cast<char*>( p_run ) + chunk_size );
	    p_run = nextof( p_run );
	 }
	 nextof( p_run ) = nullptr;
      }

      static void*& nextof( void* _p )
      {
	 return *(static_cast<void**>( _p ));
      }

      std::size_t alloc_size ()
      {
	 std::size_t chunk_sz = std::max( __USER_CHUNK_SIZE, sizeof(void*) );
	 chunk_sz += chunk_sz % 2;
	 /* To alignment, more restrictions are required here n*/
	 return chunk_sz;
      }

      std::size_t header_size ()
      {
	 return sizeof( MemBlock_List );
      }


   private:
      //std::size_t InitNum;
      std::size_t GrowNum;
      void*       MemBlock_List;
      void*       p_available;
      std::size_t chunk_size;
   };
}