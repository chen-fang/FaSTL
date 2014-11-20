#pragma once

/* Level 2 */

// Assumption #1
// ---> in template parameter: __chunk_sz >= sizeof(void*)
// Assumption #2:
// ---> in allocate( n ): n <= __chunk_sz

#include "include_header.h"
#include "malloc_alloc.hpp"

namespace fastl
{
   // BEGIN OF NAMESPACE
   //
   template< std::size_t __chunk_sz,
	     typename __Alloc = fastl :: malloc_alloc >
   class coherent_freelist : public __Alloc
   {
   public:
      coherent_freelist ( std::size_t _chunk_num )
      {
#ifdef DUMP_FREELIST
	 std::cout << "freelist( num_chunk )" << std::endl;
#endif

	 static_assert( __chunk_sz > 0, "__chunk_sz <= 0 !!! " );
	 expand( _chunk_num );
      }

      ~coherent_freelist()
      {
#ifdef DUMP_FREELIST
	    std::cout << "=================== destruct--------------: " << *i << std::endl;
#endif

	    __Alloc :: deallocate( p_head );
      }

      void* allocate ( std::size_t _n )
      {
	 if( _n > _chunk_sz || p_available == nullptr )
	 {
	    return nullptr;
	 }
	 // if( _n == 0 ) ??? neccessary ???

	 void* p_ret = p_available;
	 p_available = nextof( p_available );

	 return p_ret;
      }

      void deallocate( void* _p )
      {
	 if( _p != nullptr )
	 {
	    void* p_tmp = p_available;
	    p_available =  _p;
	    nextof( p_available ) = p_tmp;

#ifdef DUMP_FREELIST
	    std::cout <<"### deallocate:\t" << _p << std::endl;
	    std::cout <<"### next:\t" << p_tmp << std::endl << std::endl;
#endif
	 }
      }


   protected:
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
	 p_head = p_available = static_cast<char*>(__Alloc :: allocate( buffer_size ));
	 segregate( _n_chunks, chunk_sz );

#ifdef DUMP_FREELIST
	 std::cout << "--------------- expand -------------------" << std::endl;
	 std::cout << "chunk_size = " << chunk_sz << std::endl;
	 std::cout << "num_chunks = " << _n_chunks << std::endl;
	 std::cout << "buffer_size = " << buffer_size << std::endl;
	 std::cout << p_available << " --- --- > " << p_available + buffer_size << std::endl;
	 std::cout << "------------------------------------------" << std::endl;
#endif
      }

      void segregate( std::size_t _n_chunks, std::size_t _chunk_sz )
      {
	 char* p_run = p_available;
  
	 for(std::size_t i = 1; i < _n_chunks; ++i)
	 {
	    nextof( p_run ) = static_cast<void*>(  p_run + _chunk_sz );
	    p_run = nextof( p_run );
	 }
	 nextof( p_run ) = nullptr;
      }

      static void*& nextof( void* _p )
      {
	 return *(static_cast<void**>( _p ));
      }


   private:
      //std::size_t    chunk_num;
      char*          p_head;
      char*          p_available;
   };
   //
   // END OF NAMESPACE
}
