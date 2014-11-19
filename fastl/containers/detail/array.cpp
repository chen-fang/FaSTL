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

#include "fastl/containers/array.hpp"

namespace fastl { // ----------------------------------------- BEGIN NAMESPACE 

   //.............................  LIFECYCLE  ..........................//
   
   template< typename __T, typename __A > 
   array<__T,__A>::array ( array<__T,__A>::size_type _size ) :
      p_beg( __A::allocate( ) ), p_end( p_beg + _size )
   { 
      fastl::construct_buffer<__T>( p_beg, p_end );
   }

   template< typename __T, typename __A > 
   array<__T,__A>::array ( array<__T,__A>::size_type _size,
			   array<__T,__A>::const_reference _elem ) :
      p_beg( __A::allocate( ) ), p_end( p_data + _size )
   { 
      fastl::construct_buffer<__T>( p_beg, p_end, _elem );
   }

   template< typename __T, typename __A > 
   array<__T,__A>::array ( array<__T,__A>::size_type _size,
			   array<__T,__A>::const_iterator _itr ) :
      p_beg( __A::allocate( ) ), p_end( p_beg + _size )
   { 
      fastl::uninitialized_copy<__T>( p_beg, _itr, _itr + _size );
   }

   template< typename __T, typename __A > 
   array<__T,__A>::array ( const array<__T,__A> & _clone ) :
      p_beg( __A::allocate( ) ), p_end( p_beg + _size )
   { 
      fastl::uninitialized_copy<__T>( p_beg, _clone.begin(), _clone.end() );
   }

   template< typename __T, typename __A >
   array<__T,__A>::array ( array<__T,__A>&& _other ) :
      p_beg( _other.p_beg ), p_end( _other.p_end )
   {
      _other.p_beg = nullptr;
      _other.p_end = nullptr;
   }
  
   template< typename __T, typename __A > 
   array<__T,__A>::~array ( )
   { 
      fastl::destroy_buffer<__T>( p_beg, p_end );
      __A::deallocate( p_beg );
      p_end( nullptr );
   }

   //...........................  ASSIGNMENT  ..........................//
   
   template< typename __T, typename __A > 
   inline
   array<__T,__A> &
   array<__T,__A>::operator= ( const array<__T,__A> & _vrhs )
   {
      if ( p_beg != _vrhs.begin() )
      {
	 fastl::assign_from( p_beg , _vrhs.begin ( ), _vrhs.end() );
      }
      return *this;
   }

   template< typename __T, typename __A > 
   inline
   array<__T,__A> &
   array<__T,__A>::operator= ( array<__T,__A>::const_reference _rhs )
   {
      for ( iterator p = p_beg; p != p_end; ++p ) { *p = _rhs; }
      return *this;
   }

   template< typename __T, typename __A >
   inline
   array<__T,__A> &
   array<__T,__T>::operator= ( array&& _other )
   {
      p_beg = _other.p_beg;
      p_end = _other.p_end;
      _other.p_beg = nullptr;
      _other.p_end = nullptr;
   }
   //.............................  ACCESS  ............................//

   // const

   template< typename __T, typename __A > 
   inline
   array<__T,__A>::size_type
   array<__T,__A>::size ( )
   {
      return ( p_end - p_beg); // ptrdiff_t to size_t implicit cast
   }

   template< typename __T, typename __A > 
   inline
   array<__T,__A>::const_iterator
   array<__T,__A>::begin ( ) const
   {
      return p_beg;
   }


   template< typename __T, typename __A > 
   inline
   array<__T,__A>::const_iterator
   array<__T,__A>::end ( ) const
   {
      return p_end;
   }

   template< typename __T, typename __A > 
   inline
   array<__T,__A>::const_reference
   array<__T,__A>::front ( ) const
   {
      return (*p_beg);
   }


   template< typename __T, typename __A > 
   inline
   array<__T,__A>::const_reference
   array<__T,__A>::back ( ) const
   {
      return ( *(p_end-1) );
   }

   template< typename __T, typename __A > 
   inline
   array<__T,__A>::const_reference
   array<__T,__A>::operator[] ( array<__T,__A>:size_type _i ) const
   {
      return ( *(p_beg+_i) );
   }

   // mutators

   template< typename __T, typename __A > 
   inline
   array<__T,__A>::iterator
   array<__T,__A>::begin ( )
   {
      return p_beg;
   }


   template< typename __T, typename __A > 
   inline
   array<__T,__A>::iterator
   array<__T,__A>::end ( )
   {
      return p_end;
   }

   template< typename __T, typename __A > 
   inline
   array<__T,__A>::reference
   array<__T,__A>::front ( )
   {
      return (*p_beg);
   }

   template< typename __T, typename __A > 
   inline
   array<__T,__A>::reference
   array<__T,__A>::back ( )
   {
      return ( *(p_end-1) );
   }

   template< typename __T, typename __A > 
   inline
   array<__T,__A>::reference
   array<__T,__A>::operator[] ( array<__T,__A>:size_type _i )
   {
      return ( *(p_beg+_i) );
   }

   //.............................  OPERATORS  .........................//
  
   template< typename __T, typename __A > 
   inline
   void
   array<__T,__A>::reinitialize ( )
   {
      fastl::destroy_buffer<__T> ( p_beg, p_end );
      fastl::construct_buffer<__T> ( p_beg, p_end ):
   }
 

   this_type & operator- ()
   {
      // bit shift
   }

   this_type operator+ ( const this_type& _rhs ) const
   {
      this_type tmp( _rhs.size() );
      for( std::size_t i = 0; i < tmp.size(); ++i )
      {
	 tmp[i] = v1[i] + v2[i];
      }
      return tmp;
   }

   this_type operator- ( const this_type& _rhs ) const
   {
      this_type tmp( _rhs.size() );
      for( std::size_t i = 0; i < tmp.size(); ++i )
      {
	 tmp[i] = v1[i] - v2[i];
      }
      return tmp;
   }

   this_type operator* ( const this_type& _rhs ) const
   {
      this_type tmp( _rhs.size() );
      for( std::size_t i = 0; i < tmp.size(); ++i )
      {
	 tmp[i] = v1[i] * v2[i];
      }
      return tmp;
   }

   this_type operator/ ( const this_type& _rhs ) const
   {
      this_type tmp( _rhs.size() );
      for( std::size_t i = 0; i < tmp.size(); ++i )
      {
	 tmp[i] = v1[i] / v2[i];
      }
      return tmp;
   }

   this_type operator% ( const this_type& _rhs ) const
   {
      this_type tmp( _rhs.size() );
      for( std::size_t i = 0; i < tmp.size(); ++i )
      {
	 tmp[i] = v1[i] % v2[i];
      }
      return tmp;
   }


   this_type & operator+= ( const this_type& _rhs )
   {
      for( std::size_t i = 0; i < _rhs.size(); ++i )
      {
	 (*this)[i] += _rhs[i];
      }
      return *this;
   }

   this_type & operator-= ( const this_type& _rhs )
   {
      for( std::size_t i = 0; i < _rhs.size(); ++i )
      {
	 (*this)[i] -= _rhs[i];
      }
      return *this;
   }

   this_type & operator*= ( const this_type& _rhs )
   {
      for( std::size_t i = 0; i < _rhs.size(); ++i )
      {
	 (*this)[i] *= _rhs[i];
      }
      return *this;
   }

   this_type & operator/= ( const this_type& _rhs )
   {
      for( std::size_t i = 0; i < _rhs.size(); ++i )
      {
	 (*this)[i] /= _rhs[i];
      }
      return *this;
   }

} // ---------------------------------------------------------- END NAMESPACE

#endif // __ARRAY_IPP_INCLUDED_

//---------------------------------------------------------------------------//
//                           EOF array.ipp
//---------------------------------------------------------------------------//


