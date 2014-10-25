#pragma once

/* Level 2 */

// Assumption #1
// ---> in template parameter: __chunk_sz >= sizeof(void*)
// Assumption #2:
// ---> in allocate( n ): n <= __chunk_sz

#include "common_header.h"

#include "malloc_alloc.hpp"
#include "policy/policy.h"

namespace fastl
{
   template< std::size_t __chunk_sz,
	     std::size_t BOUNDARY = 0,
	     typename __Alloc = fastl :: malloc_alloc,
	     typename __Align = fastl :: Alignment<BOUNDARY> >
   class coherent_freelist : public __Alloc
   {
   public:
      coherent_freelist( std::size_t _buffer_size )
      {
	 static_assert( __chunk_sz > 0, "__chunk_sz <= 0 !!! " );

	 std::size_t chunk_sz = std::max( __chunk_sz, sizeof(void*) );
	 chunk_sz += chunk_sz % 2;
	 __Align :: Make_Aligned( chunk_sz );

	 std::size_t n_chunks = _buffer_size / __chunk_sz;
	 _buffer_size = n_chunks * chunk_sz;

	 p_head = p_available = __Alloc :: allocate( _buffer_size );
	 segregate( n_chunks, chunk_sz );
      }


      ~coherent_freelist()
      {
	 __Alloc :: deallocate( p_head );
      }

      inline void* allocate( std::size_t _n )
      {
	 if( _n > __chunk_sz || _n <0 )
	    return nullptr;

	 void* p_ret = p_available;
	 if( p_ret != nullptr )
	 {
	    p_available = nextof( p_available );
	    return p_ret;
	 }
	 return nullptr;
      }

      inline void deallocate( void* _p )
      {
	 if( _p != nullptr )
	 {
	    void* p_tmp = p_available;
	    p_available =  _p;
	    nextof( p_available ) = p_tmp;
	 }
      }


   private:
      inline void segregate( std::size_t n_chunks, std::size_t chunk_sz )
      {
	 void* p_run = p_available;
  
	 for(std::size_t i = 1; i < n_chunks; ++i)
	 {
	    nextof( p_run ) = static_cast<void*>( static_cast<char*>( p_run ) + chunk_sz );
	    p_run = nextof( p_run );
	 }
	 nextof( p_run ) = nullptr;
      }

      static void*& nextof( void* _p )
      {
	 return *(static_cast<void**>( _p ));
      }


   private:
      void* p_head;
      void* p_available;
   };
}
