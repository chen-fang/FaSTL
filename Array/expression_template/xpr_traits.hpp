#pragma once

//#include "expression.hpp"
//#include "Op.hpp"

#include "include_array.h"
#include <iostream>

template< typename X >
struct traits
{
#ifdef DUMP
   traits() {std::cout << "Take copy" << std::endl;}
#endif
   typedef X                              type;
};

template<>
struct traits< array_type >
{
#ifdef DUMP
   traits() {std::cout << "Take reference" << std::endl;}
#endif
   typedef const_array_reference_type     type;
};


// // expression (OP) expression
// template< typename T1, typename T2, typename OP >
// struct XPRtraits
// {
//    typedef Xpr< T1, T2, OP >                     type;
// };

// // array + array
// template<>
// struct XPRtraits< array_type, array_type, OpAdd >
// {
//    typedef Leaf< V_p_W >                         type;
// };
// // array - array
// template<>
// struct XPRtraits< array_type, array_type, OpSub >
// {
//    typedef Leaf< V_m_W >                         type;
// };

// // array (OP) expression
// template< typename X, typename OP >
// struct XPRtraits< array_type, X, OP >
// {
//    typedef Xpr< Leaf<array_type>, X, OP >        type;
// };

// // expression (OP) array
// template< typename X, typename OP >
// struct XPRtraits< X, array_type, OP >
// {
//    typedef Xpr< X, Leaf<array_type>, OP >        type;
// };



