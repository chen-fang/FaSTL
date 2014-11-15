#pragma once

/* Level 2 */

// Assumption #1
// ---> in template parameter: __chunk_sz >= sizeof(void*)
// Assumption #2:
// ---> in allocate( n ): n <= __chunk_sz

#include "common_header.h"

#include "malloc_alloc.hpp"
#include <list>

namespace fastl
{
   template< std::size_t __chunk_sz,
	     typename __Alloc = fastl :: malloc_alloc >
   class coherent_freelist : public __Alloc
   {
   public:
      coherent_freelist ( std::size_t _init, std::size_t _grow )
	 : Init(_init), Grow(_grow)
      {
	 static_assert( __chunk_sz > 0, "__chunk_sz <= 0 !!! " );
	 expand( Init );
      }

      ~coherent_freelist()
      {
	 std::list<void*>::iterator i;
	 for( i = MemBlock_list.begin(); i != MemBlock_list.end(); ++i )
	 {
	    __Alloc :: deallocate( *i );

	    std::cout << "=================== destruct------------: " << *i << std::endl;
	 }
      }

      void* allocate ()
      {
	 if( p_available == nullptr )
	 {
	    std::cout << "!!! Not enouth space: expand !!!" << std::endl;
	    expand( Grow );
	 }

	 void* p_ret = p_available;
	 p_available = nextof( p_available );

	 std::cout << "### allocate:\t" << p_ret << std::endl;
	 std::cout << "### next:\t" << p_available << std::endl << std::endl;

	 return p_ret;
      }

      void deallocate( void* _p )
      {
	 if( _p != nullptr )
	 {
	    void* p_tmp = p_available;
	    p_available =  _p;
	    nextof( p_available ) = p_tmp;

	    std::cout <<"### deallocate:\t" << _p << std::endl;
	    std::cout <<"### next:\t" << p_tmp << std::endl << std::endl;
	 }
      }


   private:
      std::size_t alloc_size ()
      {
	 std::size_t chunk_sz = std::max( __chunk_sz, sizeof(void*) );
	 chunk_sz += chunk_sz % 2;
	 return chunk_sz;
      }

      void expand ( std::size_t _n_chunks )
      {
	 std::size_t chunk_sz = alloc_size();
	 std::size_t buffer_size = _n_chunks * chunk_sz;
	 p_available = __Alloc :: allocate( buffer_size );
	 MemBlock_list.push_front( p_available );
	 segregate( _n_chunks, chunk_sz );

	 std::cout << "--------------- expand -------------------" << std::endl;
	 std::cout << "chunk_size = " << chunk_sz << std::endl;
	 std::cout << "num_chunks = " << _n_chunks << std::endl;
	 std::cout << "buffer_size = " << buffer_size << std::endl;
	 std::cout << p_available << " --- --- > " << p_available + buffer_size << std::endl;
	 std::cout << "------------------------------------------" << std::endl;
      }

      void segregate( std::size_t _n_chunks, std::size_t _chunk_sz )
      {
	 void* p_run = p_available;
  
	 for(std::size_t i = 1; i < _n_chunks; ++i)
	 {
	    nextof( p_run ) = static_cast<void*>( static_cast<char*>( p_run ) + _chunk_sz );
	    p_run = nextof( p_run );
	 }
	 nextof( p_run ) = nullptr;
      }

      static void*& nextof( void* _p )
      {
	 return *(static_cast<void**>( _p ));
      }


   private:
      std::size_t Init;
      std::size_t Grow;

      void* p_available;
      std::list<void*> MemBlock_list;
   };
}
