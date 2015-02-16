#pragma once

/*
 * Level 1
 * Allocation from the system directly.
 * This is the base allocator for all allocators.
 */

#include <cstddef>   // provides: size_t, nullptr
#include <cstdlib>   // provides: malloc, free
#include <cstring>   // provides: memcpy
#include <iostream>  // provides: cout
#include <cmath>     // provides: log2

#include "helper/help.h"

namespace fastl
{
   /* Template parameter <__Tag> is set to provide uniform interface  */
   template< std::size_t __TAG = 0 >
   
   struct malloc_alloc
   {
      malloc_alloc ()
      {
#ifdef DUMP_MALLOC
	 std::cout << "malloc_alloc()" << std::endl;
#endif
      }
      malloc_alloc ( std::size_t _init )                    {}
      malloc_alloc ( std::size_t _init, std::size_t _grow ) {}


      inline void* allocate( std::size_t _n )
      {
	 return std::malloc( fastl :: detail :: bs_if_equal( _n, 0, ALLOC_0, _n ) );
      }

      inline void deallocate( void* _p )
      {
	 std::free( _p );
      }
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
   // END OF NAMESPACE //
}
