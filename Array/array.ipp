// -------------------------------- *- C++ -* ------------------------------ //
// ------------------------* TEMPLATE IMPLEMENTATION *---------------------- //
// ------------------------------------------------------------------------- //
//! \file  See fastl/containers/array.hpp
//! \brief implementation of templates
//
// ------------------------------------------------------------------------- //
/** *************************************************************************
 *  \author     : Rami M. Younis
 *  \created    : 11/03/2014
 *  \revised    : 11/17/2014
 *  \version    : 0.0.0
 *  \warning    : 
 *  Target MCU  : Generic
 *  Editor TABs : 3
 *  Editor      : emacs
 *  Auto Style  : stroustrup
 ** ************************************************************************ */
/** **************************************************************************
 * Copyright (c) 2014 by Rami Younis,
 * Future Reservoir Simulation Systems & Technology (FuRSST)
 * The University of Tulsa, Tulsa OK
 * http://fursst.utulsa.edu
 *
 * Permission to use, copy, modify, and/or distribute this software and/or its
 * documentation for educational, research, and not-for-profit purposes,
 * without fee and without a signed licensing agreement, is hereby granted,
 * provided that the above copyright notice and this permission notice
 * appear in all copies, modifications, and distributions. Otherwise, all
 * rights are reserved.
 *
 * This software is distributed in the hope that it will be useful, but no
 * representations are made about the suitability of this software for any
 * purpose. It is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  It is
 * provided "as is" without express or implied warranty.
 ** ************************************************************************ */
#ifndef __ARRAY_IPP_INCLUDED_
#define __ARRAY_IPP_INCLUDED_

#include "array.hpp"
#include "../Initialization/construct.hpp"


namespace fastl { // ----------------------------------------- BEGIN NAMESPACE 

   //.............................  LIFECYCLE  ..........................//
   template< typename __A >
   array<__A> :: array ( ) :
      N(0), p_beg(nullptr)
   {  /* void */  }

   template< typename __A > 
   array<__A> :: array ( array<__A>::size_type _size ) :
      N( _size ), p_beg( static_cast<double *>(__A::allocate( _size*sizeof(double) )) )
   {
      set_zero( );
   }

   template< typename __A > 
   array<__A>::array ( array<__A>::size_type _size,
		       array<__A>::const_reference _elem ) :
      N(_size), p_beg( static_cast<double *>(__A::allocate( _size*sizeof(double) )) )
   {
      set_value ( _elem );
   }

   template< typename __A > 
   array<__A> :: array ( const array<__A> & _clone ) :
      N( _clone.size() ), p_beg( static_cast<double *>(__A::allocate( _clone.size()*sizeof(double) )) )
   { 
      //copy_from ( _clone );
      typedef array<__A>:: value_type T;
      fastl::CTR<T>:: uninitialized_copy( p_beg, _clone.p_beg, _clone.p_beg+N );
   }

   template< typename __A >
   array<__A> :: array ( array<__A> && _other )
   {
      N = _other.N;
      p_beg = _other.p_beg;

      _other.p_beg = nullptr;
   }
  
   template< typename __A > 
   array<__A> :: ~array ( )
   { 
      __A::deallocate( static_cast<void *>(p_beg) ); 
   }

   //...........................  ASSIGNMENT  ..........................//

   template< typename __A > 
   inline
   array<__A> &
   array<__A> :: operator= ( array<__A>::const_reference _s_rhs )
   {
      set_value ( _s_rhs );
      return *this;
   }
   
   template< typename __A > 
   inline
   array<__A> &
   array<__A> :: operator= ( const array<__A> & _v_rhs )
   {
      /* Possible bug:
       *    - not neccessarily 'un-initialized-copy'
       */
      typedef array<__A>::value_type   T;

      if( p_beg == _v_rhs.begin() )
	 return *this;

      resize( _v_rhs.size() );
      fastl::CTR<T>:: uninitialized_copy( p_beg, _v_rhs.begin(), _v_rhs.end() );
      return *this;
   }

   #ifdef RVALUE
   template< typename __A >
   inline
   array<__A> &
   array<__A> :: operator= ( array<__A> && _v_rhs )
   {
      typedef array<__A>::pointer pointer;
      pointer p_dealloc = p_beg;

      N = _v_rhs.N;
      p_beg = _v_rhs.p_beg;

      _v_rhs.p_beg = p_dealloc;
      return *this;
   }
   #endif

   template< typename __A >
   template< typename __Xpr >
   array<__A> &
   array<__A> :: operator= ( const __Xpr & _x_rhs )
   {
      for( std::size_t i = 0; i < _x_rhs.size(); ++i )
      {
	 p_beg[i] = _x_rhs[i];
      }
      return *this;
   }
   //.............................  ACCESS  ............................//

   template< typename __A > 
   inline
   typename array<__A>::size_type
   array<__A>::size ( ) const
   {
      return N;
   }

   template< typename __A > 
   inline
   bool
   array<__A> :: is_zero ( ) const
   {
      bool isz                      = true;
      const_iterator  __restrict pe = p_beg + N;
      iterator        __restrict p  = p_beg;
      while ( isz & (p!=pe) ) 
      {
   	 if ( *p != 0.0 ) isz = false;
   	 ++p;
      }
      return isz;
   }

   template< typename __A > 
   inline
   typename array<__A>::const_iterator
   array<__A> :: begin ( ) const
   {
      return p_beg;
   }

   template< typename __A > 
   inline
   typename array<__A>::const_iterator
   array<__A> :: end ( ) const
   {
      return ( p_beg + N );
   }

   template< typename __A > 
   inline
   typename array<__A>::const_reference
   array<__A> :: front ( ) const
   {
      return (*p_beg);
   }


   template< typename __A > 
   inline
   typename array<__A>::const_reference
   array<__A> :: back ( ) const
   {
      return p_beg[N-1];
   }

   template< typename __A > 
   inline
   typename array<__A>::const_reference
   array<__A> :: operator[] ( array<__A>::size_type _i ) const
   {
      return ( *(p_beg+_i) );
   }

   // mutators

   template< typename __A > 
   inline
   typename array<__A>::iterator
   array<__A> :: begin ( )
   {
      return p_beg;
   }


   template< typename __A > 
   inline
   typename array<__A>::iterator
   array<__A> :: end ( )
   {
      return (p_beg + N);
   }

   template< typename __A > 
   inline
   typename array<__A>::reference
   array<__A> :: front ( )
   {
      return (*p_beg);
   }


   template< typename __A > 
   inline
   typename array<__A>::reference
   array<__A> :: back ( )
   {
      return p_beg[N-1];
   }

   template< typename __A > 
   inline
   typename array<__A>::reference
   array<__A> :: operator[] ( array<__A>::size_type _i )
   {
      return ( *(p_beg+_i) );
   }

   //.............................  OPERATORS  .........................//
  
   template< typename __A > 
   inline
   void array<__A>::set_zero ( )
   {
      typedef typename array<__A>::value_type T;
      fastl :: CTR<T> :: set_zero( p_beg, p_beg+N );
   }

   template< typename __A > 
   inline
   void array<__A>::set_value ( const_reference _value )
   {
      typedef array<__A>:: value_type T;
      fastl :: CTR<T> :: set_value( p_beg, p_beg+N, _value );
   }

   template< typename __A >
   inline
   bool array<__A> :: resize( array<__A>::size_type _new_size )
   {
      /* Default: keep contents */
      return resize_keep( _new_size );
   }

   template< typename __A >
   inline
   bool array<__A> :: resize_keep( array<__A>::size_type _new_size )
   {
      /* keep contents after resize */
      bool is_successful = true;
      if(  N > _new_size )      N = _new_size;
      else
      {
	 typedef array<__A>::pointer      pointer;
	 typedef array<__A>::value_type   T;

	 pointer p_new = static_cast<pointer>( __A::allocate( _new_size * sizeof(T) ) );

	 if( p_new != nullptr )
	 {
	    fastl::CTR<T>::set_zero( p_new, p_new+_new_size );
	    fastl::CTR<T>::uninitialized_copy( p_new, p_beg, p_beg+N );

	    pointer p_dealloc = p_beg;
	    N = _new_size;
	    p_beg = p_new;

	    __A::deallocate( p_dealloc );
	 }
	 else
	 {
	    is_successful = false;
	 }
      }
      return is_successful;
   }

   template< typename __A >
   inline
   bool array<__A> :: resize_discard ( array<__A>::size_type _new_size )
   {
      /* discard contents after resize */
      bool is_successful = true;
      if(  N > _new_size )      N = _new_size;
      else
      {
	 typedef array<__A>::pointer      pointer;
	 typedef array<__A>::value_type   T;
	 pointer p_new = static_cast<pointer>( __A::allocate( _new_size * sizeof(T) ) );

	 if( p_new != nullptr )
	 {
	    pointer p_dealloc = p_beg;
	    N = _new_size;
	    p_beg = p_new;
	    __A::deallocate( p_dealloc );
	 }
	 else
	 {
	    is_successful = false;
	 }
      }
      return is_successful;
   }

   template< typename __A >
   inline
   array<__A>
   array<__A> :: operator+ ( const array<__A>& _vec )
   {
      // assume same size for now
      array<__A> tmp( _vec.size() );
      for( std::size_t i = 0; i < _vec.size(); ++i )
      {
	 tmp[i] = p_beg[i] + _vec[i];
      }
      return tmp;
   }


   // debug
   template< typename __A>
   inline
   void array<__A> :: print ()
   {
      for( std::size_t i = 0; i < N; ++i )
      {
	 std::cout << p_beg[i] << "   ";
      }
      std::cout << std::endl;
   }

   template< typename __A>
   inline
   void array<__A> :: print ( std::size_t first_n )
   {
      for( std::size_t i = 0; i < first_n; ++i )
      {
	 std::cout << p_beg[i] << "   ";
      }
      std::cout << std::endl;
   }
   //.............................  DETAIL .............................//
  

   // template< typename __A > 
   // inline
   // void
   // array<__A>::copy_from ( const_iterator __restrict _p_rhs ) // unaliased restrict ptrs
   // {
   //    for( size_type i=0; i<N; ++i) p_beg[i] = _p_rhs[i];
   //    //    std::memcpy( p_beg, _p_rhs, sizeof(double)*N );
   // }

   // template< typename __A > 
   // inline
   // void
   // array<__A>::mv_copy_from ( const_iterator _p_rhs ) // possibly aliased
   // {
   //    for( size_type i=0; i<N; ++i) p_beg[i] = _p_rhs[i];    
   //    //    std::memmove( p_beg, _p_rhs, sizeof(double)*N );
   // }


} // ---------------------------------------------------------- END NAMESPACE

//#include "fastl/array_operators.ipp"

#endif // __ARRAY_IPP_INCLUDED_

//---------------------------------------------------------------------------//
//                           EOF array.ipp
//---------------------------------------------------------------------------//


