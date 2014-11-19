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
      inline T* do_uninitialized_copy ( T* _dest, T* _start, T* _end, std::false_type )
      {
	 T* dest = _dest;
	 T* p = _start;
	 while( p != _end )
	 {
	    *dest = *_start;
	    ++p;
	    ++dest;
	 }
	 return _dest;
      }
      // trivial
      template< typename T >
      inline T* do_uninitialized_copy ( T* _dest, T* _start, T* _end, std::true_type )
      {
	 void* p_ret = std::memmove ( static_cast<void*>(_dest),
				     static_cast<void*>(_start),
				     ( _end - _start ) * sizeof(T) );
	 return static_cast<T*>( p_ret );
      }
   }
}

namespace fastl
{
   template< typename T >
   inline T* uninitialized_copy ( T* _dest, T* _start, T* _end )
   {
      return fastl :: impl :: do_uninitialized_copy( _dest, _start, _end, std::is_trivial<T>() );
   }
}
