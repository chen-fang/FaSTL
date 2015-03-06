// -------------------------------- *- C++ -* ------------------------------ //
// -------------------------------* TEMPLATE *------------------------------ //
// ------------------------------------------------------------------------- //
//! \file  array.hpp
//! \brief Runtime fixed-size heap array container
//
// ------------------------------------------------------------------------- //
/** *************************************************************************
 *  \author     : Rami M. Younis
 *  \created    : 11/03/2014
 *  \revised    : 
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

// modified by: Chen Fang
// date:        02/14/2014

#pragma once

#include <cstddef> // provides size_t ptrdiff_t
#include <iostream>

//#include "malloc_alloc.hpp"
#include "../Memory/memory.h"


namespace fastl { // ------------------------------------------ BEGIN NAMESPACE 

   // --------------------------------  ARRAY  ------------------------------ //
   /** \class array
    *  
    *  Runtime fixed-size heap array container
    **/
   // ----------------------------------------------------------------------- //
   template< typename __Alloc = fastl::singleton<> >
   //fastl::malloc_alloc<> >
   class array
   {
    
   protected:
      typedef array                                          this_type;
   public:
      typedef double                                         value_type;
      typedef double *                                       pointer;
      typedef const double *                                 const_pointer;
      typedef double &                                       reference;
      typedef double                                         const_reference;
      typedef pointer                                        iterator;
      typedef const_pointer                                  const_iterator;
      typedef std::size_t				     size_type;
      typedef std::ptrdiff_t                                 difference_type;
      typedef __Alloc                                        allocator_type;
    
   public:
      //.............................  LIFECYCLE  ..........................//
      
      // Below is commneted out for test purpose.
      // Should restore when done.
      //explicit array ();    

      // default value is provided for test purpose.
      // should delete when done.
      explicit array ( size_type _size = 1 );
      array ( size_type _size, const_reference _elem );
      array ( const this_type & _clone );
      array ( array && _other );
      ~array ( );
     
      //...........................  ASSIGNMENT  ..........................//

      this_type & operator= ( const_reference   _s_rhs );
      this_type & operator= ( const this_type & _v_rhs );

      #ifdef RVALUE
      this_type & operator= ( this_type &&      _v_rhs );
      #endif

      /* for expression template */
      template< typename __Xpr >
      this_type & operator= ( const __Xpr & _x_rhs );
     
      //.............................  ACCESS  ............................//
     
      size_type        size    ( ) const;
      bool             is_zero ( ) const;

      const_iterator   begin ( ) const;
      const_iterator   end   ( ) const;
      const_reference  front ( ) const;
      const_reference  back  ( ) const;
      const_reference  operator[] ( size_type _i ) const;
    
      iterator         begin ( );
      iterator         end   ( );
      reference        front ( );
      reference        back  ( );
      reference        operator[] ( size_type _i );
     
      //.............................  OPERATORS  .........................//
      void             set_zero ( );
      void             set_value( const_reference _rhs );

      bool             resize         ( size_type _new_size );
      bool             resize_keep    ( size_type _new_size );
      bool             resize_discard ( size_type _new_size );


      // assume both vectors are of the same size FOR NOW
      template< typename __a >
      friend array<__a> operator+ ( const array<__a>& _vec1, const array<__a> & _vec2 ); 

      // debug
      void print ();
      void print ( std::size_t first_n );
      
   private:
      size_type        N;
      pointer          p_beg;

   }; /* end of class: array */
  
  
} /* end of namespace */

#include "array.ipp"
#include "expression_template/expression.hpp"


//---------------------------------------------------------------------------//
//                           EOF array.hpp
//---------------------------------------------------------------------------//


