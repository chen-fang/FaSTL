#pragma once

//#include "ADscalarX.hpp"
#include "ADtraits.hpp"
//#include "expression_template/expression.hpp"

template< typename X >
class ADscalarX;

/* Purpose:
 * To determine the return type, according to the input type(s) & the operation type.
 * 
 * Three possible types that may be involved in the operations:
 * 1) scalar
 * 2) ADscalar
 * 3) ADscalarX<X>
 */

template< typename Left, typename Right >
inline
ADscalarX< typename ADtraits< Left, Right, OpAdd > :: xpr_type >
operator+ ( const Left& _left, const Right& _right )
{
   typedef typename ADtraits< Left, Right, OpAdd >::xpr_type       Xpr_T;

#ifndef ET_TEST
   return ADscalarX<Xpr_T>( _left.value() + _right.value(),
   			    Xpr_T( _left.gradient(),
   				   _right.gradient() ) );
   
#else
   /*
    * For the purpose of looking into expression itself, value operations are
    * bypassed temporarily
    */
   return ADscalarX<Xpr_T>( 0,
			    Xpr_T( _left.gradient(),
				   _right.gradient() ) );
#endif
}


template< typename Left, typename Right >
inline
ADscalarX< typename ADtraits< Left, Right, OpMul > :: xpr_type >
operator* ( const Left& _left, const Right& _right )
{
   typedef typename ADtraits< Left, Right, OpMul >::xpr_type       Xpr_T;

#ifndef ET_TEST
   return ADscalarX<Xpr_T>( _left.value() * _right.value(),
   			    Xpr_T( _left.value(), _right.gradient(),
   				   _right.value(), _left.gradient() ) );

#else
   /*
    * For the purpose of looking into expression itself, value operations are
    * bypassed temporarily
    */
   return ADscalarX<Xpr_T>( 0,
			    Xpr_T( _left.value(), _right.gradient(),
				   _right.value(), _left.gradient() ) );
#endif
}

template< typename Right > // specialization: scalar * expression
ADscalarX< typename ADtraits< double, Right, OpMul > :: xpr_type >
inline
operator* ( double _left, const Right& _right )
{
   typedef typename ADtraits< double, Right, OpMul >::xpr_type     Xpr_T;

#ifndef ET_TEST
   return ADscalarX<Xpr_T>( _left * _right.value(),
   			    Xpr_T( _left, _right.gradient() ) );

#else
   /*
    * For the purpose of looking into expression itself, value operations are
    * bypassed temporarily
    */
   return ADscalarX<Xpr_T>( 0,
			    Xpr_T( _left, _right.gradient() ) );
#endif
}

template< typename Left > // specialization: expression * scalar
ADscalarX< typename ADtraits< Left, double, OpMul > :: xpr_type >
inline
operator* ( const Left& _left, double _right )
{
   typedef typename ADtraits< Left, double, OpMul >::xpr_type      Xpr_T;

#ifndef ET_TEST
   return ADscalarX<Xpr_T>( _left.value() * _right,
   			    Xpr_T( _left.gradient(), _right ) );

#else
   /*
    * For the purpose of looking into expression itself, value operations are
    * bypassed temporarily
    */
   return ADscalarX<Xpr_T>( 0,
			    Xpr_T( _left.gradient(), _right ) );
#endif
}


// =====================================================================================
// ================================= Unary Operations ================================== 
// =====================================================================================
template< typename X >
ADscalarX< typename ADtraits< X, OpCos > :: xpr_type >
inline
Cos( const X& _expression )
{
   typedef typename ADtraits< X, OpCos > :: xpr_type               Xpr_T;

#ifndef ET_TEST
   return ADscalarX<Xpr_T>( cos( _expression.value() ),
   			    Xpr_T( -sin( _expression.value() ),
   				   _expression.gradient() ) );

#else
   /*
    * For the purpose of looking into expression itself, value operations are
    * bypassed temporarily
    */
   typedef typename ADtraits< X, OpCos > :: xpr_type               Xpr_T;
   return ADscalarX<Xpr_T>( 0,
   			    Xpr_T( -sin( _expression.value() ),
   				   _expression.gradient() ) );
#endif
}

template< typename X >
ADscalarX< typename ADtraits< X, OpSin > :: xpr_type >
inline
Sin( const X& _expression )
{
   typedef typename ADtraits< X, OpSin >::xpr_type                 Xpr_T;

#ifndef ET_TEST
   return ADscalarX<Xpr_T>( sin( _expression.value() ),
      Xpr_T( cos( _expression.value() ),
      _expression.gradient() ) );

#else
   /*
    * For the purpose of looking into expression itself, value operations are
    * bypassed temporarily
    */
   return ADscalarX<Xpr_T>( 0,
			    Xpr_T( cos( _expression.value() ),
				   _expression.gradient() ) );
#endif
}
