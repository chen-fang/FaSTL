// -------------------------------- *- C++ -* ------------------------------ //
// -------------------------------* TEMPLATE *------------------------------ //
// ------------------------------------------------------------------------- //
//! \file  const_parameter.hpp
//! \brief MPL promotion class that returns optimal way to take const reference
//
// ------------------------------------------------------------------------- //
/** *************************************************************************
 *  \author     : Rami M. Younis
 *  \created    : 11/10/2014
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
#ifndef __CONST_PARAMETER_HPP_INCLUDED_
#define __CONST_PARAMETER_HPP_INCLUDED_

#include <type_traits> // provides is_arithmetic

namespace fastl { // ------------------------------------------ BEGIN NAMESPACE 

  namespace mpl { // ------------------------------------------ BEGIN NAMESPACE 

    template< typename __T >
    struct const_parameter
    {
    private:
      typedef std::is_arithmetic< __T >::value                  is_arith;
    public:
      typedef typename impl_const_par< __T, is_artih  >::result result;
    }; // const_parameter
  
    template< typename __T, typename __IS_ARITH >
    struct impl_const_par
    {
    public:
      typedef const  __T &          result;
    }; // impl_const_par

    template< typename __T >
    struct impl_const_par< __T, std::true_type >
    {
    public:
      typedef __T                   result;
    }; // impl_const_par

  
  } // ---------------------------------------------------------- END NAMESPACE
  
} // ---------------------------------------------------------- END NAMESPACE

#endif // __CONST_PARAMETER_HPP_INCLUDED_

//---------------------------------------------------------------------------//
//                           EOF const_parameter.hpp
//---------------------------------------------------------------------------//


