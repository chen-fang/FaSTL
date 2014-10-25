#pragma once

#include <cstring>      // provides: memcpy
#include <cstddef>      // provides: size_t
#include <type_traits>  // provides: is_trivial<T>

#include "construct.hpp"

/* uninitialized_copy
 *
 * Objective:
 * Copy to uninitialized block from source.
 *
 * 1) If T is trivial, memcpy;
 * 2) Else, call copy constructor explicitly.
 *
 */

namespace fastl
{
   namespace impl
   {
      // non-trivial
      template< typename T >
      inline T* do_uninitialized_copy ( T* _start, T* _end, T* _dest, std::false_type )
      {
	 T* p = _start;
	 T* dest = _dest;
	 while( p != _end )
	 {
	    fastl :: construct( static_cast<void*>(dest), *p );
	    ++p;
	    ++dest;
	 }
	 return _dest;
      }
      // trivial
      template< typename T >
      inline T* do_uninitialized_copy ( T* _start, T* _end, T* _dest, std::true_type )
      {
	 void* p_ret = std::memcpy ( static_cast<void*>(_dest),
				     static_cast<void*>(_start),
				     (_end - _start + 1) * sizeof(T) ); // ??? general ???
	 return static_cast<T*>( p_ret );
      }
   }
}

namespace fastl
{
   template< typename T >
   inline T* uninitialized_copy ( T* _start, T* _end, T* _dest )
   {
      return fastl :: impl :: do_uninitialized_copy( _start, _end, _dest, std::is_trivial<T>() );
   }
}
