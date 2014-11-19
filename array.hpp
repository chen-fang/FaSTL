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
#include "fastl/mpl/const_parameter.hpp" // provides const_parameter

namespace fastl { // ------------------------------------------ BEGIN NAMESPACE 

   // --------------------------------  ARRAY  ------------------------------ //
   /** \class array
    *  
    *  Runtime fixed-size heap array container
    **/
   // ----------------------------------------------------------------------- //
  template< typename __T,
	    typename __Alloc
	    >
  class array
  {
    
  protected:
    typedef array                                          this_type;
  public:
    typedef __T                                            value_type;
    typedef __T *                                          pointer;
    typedef const __T *                                    const_pointer;
    typedef & __T                                          reference;
    typedef fastl::mpl::const_parameter<__T>::result       const_reference;
    typedef pointer                                        iterator;
    typedef const_pointer                                  const_iterator;
    typedef std::size_t					   size_type;
    typedef std::ptrdiff_t                                 difference_type;
    typedef __Alloc                                        allocator_type;
    
  public:
    //.............................  LIFECYCLE  ..........................//
    
    array ( size_type _size );

    array ( size_type _size, const_reference _elem );
      
    array ( size_type _size, const_iterator _itr );
     
    template< typename __T1, typename __T2 >
    array ( const Array< __T1, __T2 > & _clone );
     
    ~array ( );
     
    //...........................  ASSIGNMENT  ..........................//
     
    template< typename __T1, typename __T2 >
    Array<__T, allocator_type> & operator= (  const Array< __T1, __T2 > & _v_rhs );
    
    Array<__T, allocator_type> & operator= ( const_reference _s_rhs );
     
    //.............................  ACCESS  ............................//
     
    size_type        size  ( ) const;

    const_iterator   begin ( ) const;
    const_iterator   end   ( ) const;
    const_reference  front ( ) const;
    const_reference  back  ( ) const;
    const_reference  operator[] ( size_type _i ) const;
     
    void             reinitialize ( );
    
    iterator         begin ( );
    iterator         end   ( );
    reference        front ( );
    reference        back  ( );
    reference        operator[] ( size_type _i );
     
    //.............................  OPERATORS  .........................//
   
    bool operator== ( const_param _v_rhs );
     
  private:
    pointer         p_data;
    const size_type c_size;
  }; // pod_array
  
  
} // ---------------------------------------------------------- END NAMESPACE

#include "fastl/containers/detail/array.ipp"

#endif // __ARRAY_HPP_INCLUDED_

//---------------------------------------------------------------------------//
//                           EOF array.hpp
//---------------------------------------------------------------------------//


