#pragma once

/* Level 1 */

#include "common_header.h"

#include "helper_function/helper_function.hpp"

namespace fastl
{
   // BEGIN OF NAMESPACE //
   //
   struct malloc_alloc
   {
      malloc_alloc ()
      {
	 std::cout << "malloc_alloc()" << std::endl;
      }
      malloc_alloc ( std::size_t _n ) {}


      inline void* allocate( std::size_t _n )
      {
	 return std::malloc( fastl :: detail :: bs_if_equal( _n, 0, ALLOC_0, _n ) );
      }

      inline void deallocate( void* _p )
      {
	 std::free( _p );
      }

      // ~malloc_alloc()
      // {
      // 	 std::cout << "malloc_alloc :: dtor" << std::endl;
      // }
   };


   struct new_alloc
   {
      inline void* allocate( std::size_t _n )
      {
	 return :: operator new( fastl :: detail :: bs_if_equal( _n, 0, ALLOC_0, _n ), std::nothrow );
      }

      inline void deallocate( void* _p )
      {
	 :: operator delete( _p, std::nothrow );
      }

   };
   //
   // END OF NAMESPACE //
}
