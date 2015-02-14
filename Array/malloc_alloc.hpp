#pragma once

/*
 * Level 1
 * Allocation from the system directly.
 * This is the base allocator for all allocators.
 */

#include <cstddef>
#include <cstdlib>

namespace fastl
{
   struct malloc_alloc
   {
      static inline void* allocate( std::size_t _n )
      {
	 return std::malloc( _n );
      }

      static inline void deallocate( void* _p )
      {
	 std::free( _p );
      }
   };
   // END OF NAMESPACE //
}
