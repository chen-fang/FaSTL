/*
 * Created by: Chen Fang
 * Date: 03/04/2015
 */

#pragma once
#include "ADunivariate.hpp"

template< typename T1, typename T2 >
inline
Xpr<T1,T2,OpAdd> operator+ ( const T1& _left, const T2& _right )
{
   return Xpr<T1,T2,OpAdd>( _left, _right );
}
