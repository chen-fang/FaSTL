#pragma once

//#include "xpr_traits.hpp"

// ============================ Addition ============================
// // // vector + vector
// inline
// //typename XPRtraits< array_type, array_type, OpAdd >::type
// V_p_W< array_type, array_type >
// operator + ( const array_type& vec1, const array_type& vec2 )
// {
//    std::cout << "V_p_W ( vec1, vec2 )" << std::endl;

//    //typedef Leaf< V_p_W > Xpr_T;
//    //typedef typename XPRtraits< array_type, array_type, OpAdd >::type Xpr_T;
//    typedef V_p_W< array_type, array_type > Xpr_T;

//    return Xpr_T( vec1, vec2 );
// }

// // vector + expression
// template< typename X >
// inline
// //typename XPRtraits< array_type, X, OpAdd >::type
// V_p_W< array_type, X >
// operator + ( const array_type& vec, const X& xpr )
// {
//    std::cout << "V_p_W ( vec, X )" << std::endl;

//    //typedef Xpr< Leaf<array_type>, X, OpAdd > Xpr_T;
//    //typedef typename XPRtraits< array_type, X, OpAdd >::type Xpr_T;
//    typedef V_p_W< array_type, X > Xpr_T;

//    return Xpr_T( vec, xpr );
// }

// // expression + vector
// template< typename X >
// inline
// //typename XPRtraits< X, array_type, OpAdd >::type
// V_p_W< X, array_type >
// operator + ( const X& xpr, const array_type& vec )
// {
//    std::cout << "V_p_W ( X, vec )" << std::endl;

//    //typedef Xpr< X, Leaf<array_type>, OpAdd > Xpr_T;
//    //typedef typename XPRtraits< X, array_type, OpAdd >::type Xpr_T;
//    typedef V_p_W< X, array_type > Xpr_T;

//    return Xpr_T( xpr, vec );
// }

// // expression + expression
// template< typename X1, typename X2 >
// inline
// //typename XPRtraits< X1, X2, OpAdd >::type
// V_p_W< X1, X2 >
// operator + ( const X1& x1, const X2& x2 )
// {
//    std::cout << "V_p_W ( X1, X2 )" << std::endl;

//    //typedef Xpr< X1, X2, OpAdd > Xpr_T;
//    //typedef typename XPRtraits< X1, X2, OpAdd >::type Xpr_T;
//    typdef V_p_W< X1,X2 > Xpr_T;
//    return Xpr_T( x1, x2 );
// }


// ============================ Multiplication ============================
// // scalar * vector
// template< typename S, typename T >
// inline
// typename std::enable_if< std::is_arithmetic<S>::value, Xpr< Literal<S>, Leaf<T>, OpMul > > :: type
// operator * ( S a, const array_type& vec )
// {
//    typedef Xpr< Literal<S>, Leaf<T>, OpMul > Xpr_T;
//    return Xpr_T( Literal<S>(a), Leaf<T>(vec) );
// }

// // vector * scalar
// template< typename T, typename S >
// inline
// typename std::enable_if< std::is_arithmetic<S>::value, Xpr< Leaf<T>, Literal<S>, OpMul > > :: type
// operator * ( const array_type& vec, S a )
// {
//    typedef Xpr< Leaf<T>, Literal<S>, OpMul > Xpr_T;
//    return Xpr_T( Leaf<T>(vec), Literal<S>(a) );
// }


// // scalar * expression
// template< typename S, typename X >
// inline
// typename std::enable_if< std::is_arithmetic<S>::value, Xpr< Literal<S>, X, OpMul > > :: type
// operator * ( S a, const X& xpr )
// {
//    typedef Xpr< Literal<S>, X, OpMul > Xpr_T;
//    return Xpr_T( Literal<S>(a), xpr );
// }

// // expression * scalar
// template< typename X, typename S >
// inline
// typename std::enable_if< std::is_arithmetic<S>::value, Xpr< X, Literal<S>, OpMul > > :: type
// operator * ( const X& xpr, S a )
// {
//    typedef Xpr< X, Literal<S>, OpMul > Xpr_T;
//    return Xpr_T( xpr, Literal<S>(a) );
// }

// // vector * vector
// template< typename S_type >
// inline
// aV_p_bW< S_type, array_type, array_type >
// operator * ( const array_type& vec1, const array_type& vec2 )
// {
// typedef typename array
//    typedef Xpr< Leaf<T>, Leaf<T>, OpMul > Xpr_T;
//    return Xpr_T( Leaf<T>(vec1), Leaf<T>(vec2) );
// }


// // expression * vector
// template< typename X, typename T >
// inline
// Xpr< X, Leaf<T>, OpMul >
// operator * ( const X& xpr, const array_type& vec )
// {
//    typedef Xpr< X, Leaf<T>, OpMul > Xpr_T;
//    return Xpr_T( xpr, Leaf<T>(vec) );
// }

