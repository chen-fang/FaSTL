#pragma once

//#include "ADunivariate.hpp"
template< typename __ALLOC >
class ADuni;

typedef ADuni<>               ADuni_type;

/* VRtraits
 * Determine whether to take copy or reference
 */
template< typename T >
struct VRtraits
{
   typedef T                        type;
};

template<>
struct VRtraits< ADuni_type >
{
   typedef const ADuni_type         type;
};


/* ValueType_Traits
 * Promote one type when two types are provided
 */
template< typename T1, typename T2 >
struct ValueType_Traits
{
   typedef T1                        value_type;
};
