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
#ifndef __ARRAY_HPP_INCLUDED_
#define __ARRAY_HPP_INCLUDED_

#include <cstddef> // provides size_t ptrdiff_t
#include "malloc_alloc.hpp"
#include <iostream>

namespace fastl { // ------------------------------------------ BEGIN NAMESPACE 

   // --------------------------------  ARRAY  ------------------------------ //
   /** \class array
    *  
    *  Runtime fixed-size heap array container
    **/
   // ----------------------------------------------------------------------- //
   template< typename __Alloc = fastl::malloc_alloc >
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
      explicit array ();    

      explicit array ( size_type _size );

      array ( size_type _size, const_reference _elem );
      
      // array ( size_type _size, const_iterator __restrict  _itr );
     
      array ( const this_type & _clone );

      array ( array && _other );
     
      ~array ( );
     
      //...........................  ASSIGNMENT  ..........................//
     
      this_type & operator= ( const this_type & _v_rhs );
    
      this_type & operator= ( const_reference   _s_rhs );

      this_type & operator= ( this_type &&      _v_rhs );

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
      bool             resize   ( size_type _n );


      // private:    
      // requires non-overlapping buffers
      // void             copy_from( const_iterator __restrict p_rhs );    
    
      // // allows buffers to intersect
      // void             mv_copy_from( const_iterator p_rhs );



   private:
      size_type        N;
      pointer          p_beg;
   }; // array
  
  
} // ---------------------------------------------------------- END NAMESPACE

#include "array.ipp"
#include "expression_template/expression.hpp"

#endif // __ARRAY_HPP_INCLUDED_

//---------------------------------------------------------------------------//
//                           EOF array.hpp
//---------------------------------------------------------------------------//


