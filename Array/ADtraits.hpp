#pragma once

//#include "expression_template/xpr_traits.hpp"
#include "expression_template/expression.hpp"
#include <iostream>

/*
 * This solves the limitation associated with partial specialization,
 * which is the number of arguments must be the same with that defined
 * in base class.
 * With varidic template, ADtraits will work in both of following forms:
 * 1) ADtraits< T1, T2, OP >
 * 2) ADtraits< X, OP >
 */
template< typename... args > 
struct ADtraits {};


/*
 * Go to: "expression_template/expression.hpp" to find corresponding
 * constructors of xpr_type.
 */
template< typename Left, typename Right >
struct ADtraits< Left, Right, OpAdd >
{
   typedef typename Left::gradient_type           V_type;
   typedef typename Right::gradient_type          W_type;
   typedef V_p_W< V_type, W_type >                xpr_type;
};

template< typename Left, typename Right >
struct ADtraits< Left, Right, OpMul >
{
   /* Important Note:
    * 1) aV_p_bW is unaware of AD. So the parameter sequence should follow its
    *    natrual order: "a-V-b-W", as is defined in its name.
    *
    * 2) operator '*' between ADscalars has its fixed "left * right" order. But
    *    its gradient type is actually:
    *    'left.value * right.gradient + right.value * left.gradient'.
    *
    * 3) To match 'aV_p_bW' with operator '*', the following 'xpr_type' is defined
    *    such that both of above can have their natural interfaces (constructors).
    */
   typedef typename Right::gradient_type          V_type;
   typedef typename Left::gradient_type           W_type;
   typedef aV_p_bW< V_type, W_type >              xpr_type;
};

template< typename Right > // specialization: scalar * expression
struct ADtraits< double, Right, OpMul >
{
   typedef double                                 S_type;
   typedef typename Right::gradient_type          V_type;
   typedef aV< V_type >                           xpr_type;
};

template< typename Left > // specialization: expression * scalar
struct ADtraits< Left, double, OpMul >
{
   typedef typename Left::gradient_type           V_type;
   typedef double                                 S_type;
   typedef aV< V_type >                           xpr_type;
};


// =====================================================================================
// ================================= Unary Operations ================================== 
// =====================================================================================
template< typename X >
struct ADtraits< X, OpCos > // Cos(X)' = -Sin(X) * X'
{
   typedef typename X::value_type                 S_type;
   typedef typename X::gradient_type              V_type;
   typedef aV< V_type>                            xpr_type;
};

template< typename X >
struct ADtraits< X, OpSin > // Sin(X)' = Cos(X) * X'
{
   typedef typename X::value_type                 S_type;
   typedef typename X::gradient_type              V_type;
   typedef aV< V_type >                           xpr_type;
};

