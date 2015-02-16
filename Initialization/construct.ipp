#include "construct.hpp"
#include "construct_detail.hpp"


namespace fastl
{
   template< typename T >
   inline
   void CTR<T> :: set_zero ( T* _p )
   {
      fastl :: impl :: do_set_zero( _p, std::is_trivial<T>() );
   }

   template< typename T >
   inline
   void CTR<T> :: set_zero ( T* _p_beg, T* _p_end )
   {
      fastl :: impl :: do_set_zero( _p_beg, _p_end, std::is_trivial<T>() );
   }

   template< typename T >
   inline
   void CTR<T> :: set_value ( T* _p, T value )
   {
      *_p = value;
   }

   template< typename T >
   inline
   void CTR<T> :: set_value ( T* _p_beg, T* _p_end, T value )
   {
      std::ptrdiff_t size = _p_end - _p_beg;
      std::size_t threshold = 10000;
      if( size <= threshold )
      {
	 fastl :: impl :: direct_assignment( _p_beg, size, value );
      }
      else
      {
	 fastl :: impl :: recursive_assignment( _p_beg, _p_end, size, threshold, value );
      }
   }

   template< typename T >
   inline
   void CTR<T> :: construct ( T* _p ) // zero_argument
   {
      fastl :: impl :: do_construct( _p, std::is_trivial<T>() );
      // fastl :: impl :: set_zero( _p );
   }

   template< typename T >
   inline
   void CTR<T> :: construct_buffer ( T* _p_beg, T* _p_end ) // zero_argument
   {
      fastl :: impl :: do_construct_buffer( _p_beg, _p_end, std::is_trivial<T>() );
      // fastl :: set_zero( _p_beg, _p_end );
   }

   template< typename T >
   template< typename T1, typename... Args >
   inline
   void CTR<T> :: construct ( T* _p, T1&& _arg1, Args&&... _args ) // nonzero_arguments
   {
      :: new ( static_cast<void*>(_p) ) T( std::forward<T1>(_arg1), 
					   std::forward<Args...>(_args)... );
   }

   // nonzero-argument: copy_ctor & move_ctor
   template< typename T >
   template< typename T1, typename... Args >
   inline
   void CTR<T> :: construct_buffer ( T* _p_beg, T* _p_end, T1&& _arg1, Args&&... _args )
   {
      T* tmp = _p_beg;
      while( tmp != _p_end )
      {
	 construct( tmp, 
		    std::forward<T1>(_arg1),
		    std::forward<Args...>(_args)... );
	 ++tmp;
      }
   }

   template< typename T >
   inline
   void CTR<T> :: destroy ( T* _p )
   {
      fastl :: impl :: do_destroy( _p, std::is_trivial<T>() );
   }

   template< typename T >
   inline
   void CTR<T> :: destroy_buffer ( T* _p_beg, T* _p_end )
   {
      fastl :: impl :: do_destroy_buffer( _p_beg, _p_end, std::is_trivial<T>() );
   }

   template< typename T >
   inline
   void CTR<T> :: uninitialized_copy ( T* _p_dest, const T* _src_beg, const T* _src_end )
   {
      fastl :: impl :: do_uninitialized_copy( _p_dest, _src_beg, _src_end, std::is_trivial<T>() );
   }

   template< typename T >
   inline
   void CTR<T> :: uninitialized_copy_mv ( T* _p_dest, const T* _src_beg, const T* _src_end )
   {
      fastl :: impl :: do_uninitialized_copy_mv( _p_dest, _src_beg, _src_end, std::is_trivial<T>() );
   }
}// End of Namespace: fastl




