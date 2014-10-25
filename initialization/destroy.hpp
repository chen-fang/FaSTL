#pragma once

#include <type_traits>

/* destroy
 *
 * Objective:
 * Call the destructor.
 *
 * 1) If the destructor is trivial, do nothing;
 * 2) Else, call the destructor explicitly.
 *
 */

// ------ destroy single object ------
namespace fastl
{
   namespace impl
   {
      // non-trivial
      template< typename T >
      inline void do_destroy( T* _p, std::false_type )
      {
	 _p -> ~T();
      }
      // trivial
      template< typename T > 
      inline void do_destroy( T* _p, std::true_type )
      { /* do nothing */ }
   }
}

namespace fastl
{
   template< typename T >
   static inline void destroy( T* _p )
   {
      fastl :: impl :: do_destroy( _p, std::is_trivial<T>() );
   }
}



// ------ destroy array ------
namespace fastl
{
   namespace impl
   {
      // non-trivial
      template< typename T >
      inline void do_destroy_array( T* _start, T* _end, std::false_type )
      {
	 T* tmp = _start;
	 while( tmp != _end )
	 {
	    //tmp -> ~T();
	    fastl :: destroy( tmp );
	    ++tmp;
	 }
      }
      // trivial
      template< typename T >
      inline void do_destroy_array( T* _start, T* _end, std::true_type )
      { /* do nothing */ }
   }
}

namespace fastl
{
   template< typename T >
   static inline void destroy_array( T* _start, T* _end )
   {
      fastl :: impl :: do_destroy_array( _start, _end, std::is_trivial<T>() );
   }
}
