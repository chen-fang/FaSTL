#pragma once

#include <new>          // provides: placement new
#include <utility>      // provides: forward
#include <iostream>
#include <type_traits>  // provides: is_trivial
#include <cstring>      // provdies: memset

// =======================================================================================
// ****************** Below are detailed functions to support CTR class ******************
// =======================================================================================
namespace fastl
{
   namespace impl
   {
      // ====================================================================== set_zero ()
      template< typename T >
      inline void do_set_zero ( T* _p, std::false_type ) // non_trivial
      {  /* do nothing */  }

      template< typename T >
      inline void do_set_zero ( T* _p, std::true_type )  // trivial
      {  *_p = (T)0;  }

      template< typename T >
      inline void do_set_zero ( T* _p_beg, T* _p_end, std::false_type ) // non_trivial
      {  /* do nothing */  }

      template< typename T >
      inline void do_set_zero ( T* _p_beg, T* _p_end, std::true_type )  // trivial
      {
   	 std::memset( static_cast<void*>(_p_beg), 0, ( _p_end-_p_beg )*sizeof(T) );
      }

      // ====================================================================== construct_base
      template< typename T >
      inline void do_non_trivial_construct ( T* _p )
      {  :: new ( static_cast<void*>(_p) ) T;  }

      template< typename T >
      inline void do_trivial_construct ( T* _p )
      {  /* do nothing */  }
      
      // ====================================================================== construct ()
      // non-trivial
      template< typename T >
      inline void do_construct ( T* _p, std::false_type )
      {  do_non_trivial_construct( _p );  }
      // trivial
      template< typename T >
      inline void do_construct ( T* _p, std::true_type )
      {	 do_trivial_construct( _p );  }

      // ====================================================================== construct_array ()
      // non-trivial
      template< typename T >
      inline void do_construct_buffer ( T* _p_beg, T* _p_end, std::false_type )
      {
	 /* Optimization Advise: Duff's device */
	 T* tmp = _p_beg;
	 while( tmp != _p_end )
	 {
	    do_non_trivial_construct( tmp );
	    ++tmp;
	 }
      }

      // trivial
      template< typename T >
      inline void do_construct_buffer ( T* _p_beg, T* _p_end, std::true_type )
      {
	 T* tmp = _p_beg;
	 while( tmp != _p_end )
	 {
	    do_trivial_construct( tmp );
	    ++tmp;
	 }
      }

      // ====================================================================== destruct_base
      template< typename T >
      inline void do_non_trivial_destroy( T* _p )
      {	 _p -> ~T();  }

      template< typename T >
      inline void do_trivial_destroy( T* _p )
      {	 /* do nothing */  }

      // ====================================================================== destruct ()
      // non-trivial
      template< typename T >
      inline void do_destroy( T* _p, std::false_type )
      {	 do_non_trivial_destroy( _p );  }
      // trivial
      template< typename T > 
      inline void do_destroy( T* _p, std::true_type )
      {	 do_trivial_destroy( _p );  }

      // ====================================================================== destruct_buffer ()
      // non-trivial
      template< typename T >
      inline void do_destroy_buffer( T* _p_beg, T* _p_end, std::false_type )
      {
	 T* tmp = _p_beg;
	 while( tmp != _p_end )
	 {
	    do_non_trivial_destroy( tmp );
	    ++tmp;
	 }
      }

      // trivial
      template< typename T >
      inline void do_destroy_buffer( T* _p_beg, T* _p_end, std::true_type )
      {
	 T* tmp = _p_beg;
	 while( tmp != _p_end )
	 {
	    do_trivial_destroy( tmp );
	    ++tmp;
	 }
      }

      // ====================================================================== uninitialized_copy()
      // non_trivial
      template< typename T >
      inline void do_uninitialized_copy ( T* _p_dest, T* _src_beg, T* _src_end, std::false_type )
      {
	 T* dest = _p_dest;
	 T* p = _src_beg;
	 while( p != _src_end )
	 {
	    *dest = *_src_beg;
	    ++p;
	    ++dest;
	 }
      }

      // trivial
      template< typename T >
      inline void do_uninitialized_copy ( T* _p_dest, T* _src_beg, T* _src_end, std::true_type )
      {
	 std::memcpy ( static_cast<void*>(_p_dest),
		       static_cast<void*>(_src_beg),
		       ( _src_end - _src_beg ) * sizeof(T) );
      }
   

      // ====================================================================== uninitialized_copy_mv
      // non_trivial
      template< typename T >
      inline void do_uninitialized_copy_mv ( T* _p_dest, T* _src_beg, T* _src_end, std::false_type )
      {
	 fastl :: impl :: do_uninitialized_copy( _p_dest, _src_beg, _src_end, std::false_type );
      }

      // trivial
      template< typename T >
      inline void do_uninitialized_copy_mv ( T* _p_dest, T* _src_beg, T* _src_end, std::true_type )
      {
	 std::memmove ( static_cast<void*>(_p_dest),
			static_cast<void*>(_src_beg),
			( _src_end - _src_beg ) * sizeof(T) );
      }

   }// End of Namespace: impl
}// End of Namespace: fastl
