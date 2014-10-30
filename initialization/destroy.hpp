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
      template< typename T >
      inline void do_non_trivial_destroy( T* _p )
      {
	 _p -> ~T();
      }

      template< typename T >
      inline void do_trivial_destroy( T* _p )
      {
	 // do nothing
      }

      // non-trivial
      template< typename T >
      inline void do_destroy( T* _p, std::false_type )
      {
	 do_non_trivial_destroy( _p );
      }
      // trivial
      template< typename T > 
      inline void do_destroy( T* _p, std::true_type )
      {
	 do_trivial_destroy( _p );
      }
   }


   template< typename T >
   static inline void destroy( T* _p )
   {
      impl :: do_destroy( _p, std::is_trivial<T>() );
   }



// ------ destroy array ------
   namespace impl
   {
      // non-trivial
      template< typename T >
      inline void do_destroy_array( T* _start, T* _end, std::false_type )
      {
	 T* tmp = _start;
	 while( tmp != _end )
	 {
	    do_non_trivial_destroy( tmp );
	    ++tmp;
	 }
      }
      // trivial
      template< typename T >
      inline void do_destroy_array( T* _start, T* _end, std::true_type )
      {
	 T* tmp = _start;
	 while( tmp != _end )
	 {
	    do_trivial_destroy( tmp );
	    ++tmp;
	 }
      }
   }


   template< typename T >
   static inline void destroy_array( T* _start, T* _end )
   {
      fastl :: impl :: do_destroy_array( _start, _end, std::is_trivial<T>() );
   }
}
