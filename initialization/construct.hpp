#pragma once
#include <new>          // provides: placement new
#include <utility>      // provides: forward
#include <iostream>
#include <type_traits>  // provides: is_trivial

/** construct
 * 
 * Objective:
 * Call the constructor, including:
 * --> default constructor
 * --> copy constructor
 * --> move constructor
 *
 */

namespace fastl
{
   namespace impl
   {
      template< typename T >
      inline void do_non_trivial_construct ( T* _p )
      {
	 :: new ( static_cast<void*>(_p) ) T;
      }

      template< typename T >
      inline void do_trivial_construct ( T* _p )
      {
	 // do nothing
      }
      

      // non-trivial
      template< typename T >
      inline void do_construct ( T* _p, std::false_type )
      {
	 do_non_trivial_construct( _p );
      }
      // trivial
      template< typename T >
      inline void do_construct ( T* _p, std::true_type )
      {
	 do_trivial_construct( _p );
      }
   }

   // zero-argument
   template< typename T >
   inline void construct ( T* _p )
   {
      std::cout << "construct(p)" << std::endl;
      impl :: do_construct ( _p, std::is_trivial<T>() );
   }

   // nonzero-argument
   template< typename T, typename T1, typename... Args >
   inline void construct ( T* _p, T1&& _arg1, Args&&... _args )
   {
      :: new ( static_cast<void*>(_p) ) T( std::forward<T1>(_arg1), 
					   std::forward<Args...>(_args)... );
   }











   // ---> default construct array
   namespace impl
   {
      // non-trivial
      template< typename T >
      inline void do_construct_array ( T* _start, T* _end, std::false_type )
      {
	 //std::cout << "non_trivial" << std::endl;
	 /* Optimization Advise:
	  *
	  * Duff's device
	  *
	  */
	 T* tmp = _start;
	 while( tmp != _end )
	 {
	    do_non_trivial_construct( tmp );
	    ++tmp;
	 }
      }

      // trivial
      template< typename T >
      inline void do_construct_array ( T* _start, T* _end, std::true_type )
      {
	 //std::cout << "trivial" << std::endl;

	 T* tmp = _start;
	 while( tmp != _end )
	 {
	    do_trivial_construct( tmp );
	    ++tmp;
	 }
      }
   }

   // zero-argument
   template< typename T >
   inline void construct_array ( T* _start, T* _end )
   {
      std::cout << "construct_array( "<< _start <<", "<< _end << " ): ";
      impl :: do_construct_array ( _start, _end, std::is_trivial<T>() );
   }

   // nonzero-argument: copy_ctor & move_ctor
   template< typename T, typename T1, typename... Args >
   inline void construct_array ( T* _start, T* _end, T1&& val, Args&&... _args )
   {
      T* tmp = _start;
      while( tmp != _end )
      {
	 construct( tmp, 
		    std::forward<T1>(val),
		    std::forward<Args...>(_args)... );
	 ++tmp;
      }
   }




















   namespace impl
   {
      // non-trivial
      template< typename T >
      inline void do_set_zero ( T* _start, T* _end, std::false_type )
      {
	 std::cout << "non-trivial" << std::endl;
	 /* do nothing */ }

      // trivial
      template< typename T >
      inline void do_set_zero ( T* _start, T* _end, std::true_type )
      {
	 std::cout << "trivial --> " << (_end-_start)*sizeof(T) << " bytes" << std::endl;
   	 std::memset( static_cast<void*>(_start),
   		      0,
   		      ( _end - _start ) * sizeof(T) );
      }
   }


   template< typename T >
   inline void set_zero ( T* _start, T* _end )
   {
      std::cout << "set_zero( "<< _start << ", "<< _end << " )\t";
      fastl :: impl :: do_set_zero( _start, _end, std::is_trivial<T>() );
   }
}
