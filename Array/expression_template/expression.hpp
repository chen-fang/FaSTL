#pragma once

#include <cstddef>
#include "xpr_traits.hpp"
#include "Op.hpp"

// // ==============================================================
// template< typename T >
// class Literal
// {
// public:
//    typedef T value_type;

//    Literal ( T literal ) : m_literal( literal ) {}
//    //Literal ( T && literal ) : m_literal( std::move(literal) ) {}

//    T operator [] ( std::size_t i )         { return m_literal; }
//    T operator [] ( std::size_t i ) const   { return m_literal; }
//    std::size_t size () const               { return 0;         }

// private:
//    T m_literal;
// };


// // ==============================================================
// template< typename T >
// class Leaf
// {
// public:
//    typedef typename T::value_type value_type;

//    Leaf ( const T& _leaf ) : m_leaf( _leaf ) {}
//    //Leaf( T && _leaf ) : m_leaf( std::move(_leaf) ) {}

//    inline value_type operator [] ( std::size_t i )         { return m_leaf[i];     }
//    inline value_type operator [] ( std::size_t i ) const   { return m_leaf[i];     }
//    inline std::size_t size () const                        { return m_leaf.size(); }

// private:
//    T m_leaf;
// };

// template<>
// class Leaf< array_type >
// {
// public:
//    typedef typename array_type::value_type value_type;

//    Leaf ( const array_type& _leaf ) : m_leaf( _leaf ) {}

//    inline value_type operator [] ( std::size_t i )         { return m_leaf[i];     }
//    inline value_type operator [] ( std::size_t i ) const   { return m_leaf[i];     }
//    inline std::size_t size () const                        { return m_leaf.size(); }

// private:
//    const array_type& m_leaf;
// };



// template< typename X_type, typename Op >
// class XprUnary
// {
// public:
//    typedef typename X_type::value_type                 value_type;
//    typedef typename traits< X_type >::type             T;

//    XprUnary( const X_type& _xpr ) : xpr(_xpr)
//    {
//       std::cout << "XprUnary" << std::endl;
//       traits<X_type>();
//    }

//    value_type operator [] ( std::size_t i )            { return Op::apply( xpr[i] ); }
//    value_type operator [] ( std::size_t i ) const      { return Op::apply( xpr[i] ); }
//    std::size_t size () const                           { return xpr.size();          }

// private:
//    T xpr;;
// };

// template< typename X1_type, typename X2_type, typename Op >
// class XprBinary
// {
// public:
//    typedef typename X1_type::value_type                value_type;
//    /*  assume T2::value_type == T1::value_type  */
//    typedef typename traits< X1_type >::type            T1;
//    typedef typename traits< X2_type >::type            T2;

//    XprBinary ( const X1_type& _xpr_1, const X2_type& _xpr_2 ) : xpr_1(_xpr_1), xpr_2(_xpr_2)
//    {
//       std::cout << "XprBinary" << std::endl;
//       traits<X1_type>();
//       traits<X2_type>();
//    }

//    //Xpr ( T1 && _left, T2 && _right ) : m_left( std::move(_left), m_right( std::move(_right) ) {}

//    value_type operator [] ( std::size_t i )
//    {
//       return Op::apply( xpr_1[i], xpr_2[i] );
//    }

//    inline value_type operator [] ( std::size_t i ) const
//    {
//       return Op::apply( xpr_1[i], xpr_2[i] );
//    }

//    inline std::size_t size () const
//    {
//       return xpr_1.size();
//    }

// private:
//    T1 xpr_1;
//    T2 xpr_2;
// };




// ==============================================================
// ================= Specific Expressions Below =================
// ==============================================================

// ============================================================== V + W
#ifdef RESTRICT
template< typename Left, typename Right >
class V_p_W
{
public:
   typedef typename array_type::value_type             value_type;
   typedef double                                      S_type;
   typedef typename traits< Left >::type               V_type;
   typedef typename traits< Right >::type              W_type;

   V_p_W ( const Left& __restrict _v, const Right& __restrict _w ) : V(_v), W(_w)
   {}

   inline value_type operator [] ( std::size_t i )            { return V[i] + W[i]; }
   inline value_type operator [] ( std::size_t i ) const      { return V[i] + W[i]; }
   inline std::size_t size () const                           { return V.size();  }

private:
   V_type V;
   W_type W;
};

#else
template< typename Left, typename Right >
class V_p_W
{
public:
   typedef typename array_type::value_type             value_type;
   typedef double                                      S_type;
   typedef typename traits< Left >::type               V_type;
   typedef typename traits< Right >::type              W_type;

   V_p_W ( const Left& _v, const Right& _w ) : V(_v), W(_w)
   {}

   inline value_type __attribute__ ((always_inline)) operator [] ( std::size_t i )            { return V[i] + W[i]; }
   inline value_type __attribute__ ((always_inline)) operator [] ( std::size_t i ) const      { return V[i] + W[i]; }
   inline std::size_t size () const                           { return V.size();  }

private:
   V_type V;
   W_type W;
};

#endif

// ============================================================== V - W
template< typename Left, typename Right >
class V_m_W
{
public:
   typedef typename array_type::value_type             value_type;
   typedef double                                      S_type;
   typedef typename traits< Left >::type               V_type;
   typedef typename traits< Right >::type              W_type;

   V_m_W ( const Left& _v, const Right& _w ) : V(_v), W(_w)
   {
#ifdef DUMP
      std::cout << "V_m_W" << std::endl;
      traits<Left>();
      traits<Right>();
#endif
   }


   inline value_type __attribute__ ((always_inline)) operator [] ( std::size_t i )            { return V[i] - W[i]; }
   inline value_type __attribute__ ((always_inline)) operator [] ( std::size_t i ) const      { return V[i] - W[i]; }
   inline std::size_t size () const                           { return V.size();  }

private:
   V_type V;
   W_type W;
};


// ============================================================== a*V + b*W
/*
 * S_type: Scalar type
 * V_type: Left expression type
 * W_type: Right expression type
 */
template< typename V, typename W >
class aV_p_bW
{
public:
   typedef double                                      a_type;
   typedef double                                      b_type;
   typedef typename traits< V >::type                  V_type;
   typedef typename traits< W >::type                  W_type;
   typedef typename array_type::value_type             value_type;

   aV_p_bW ( a_type _a, const V& _v, b_type _b, const W& _w )
      : a(_a), v(_v), b(_b), w(_w)
   {
#ifdef DUMP
      std::cout << "aV_p_bW" << std::endl;
      traits<Left>();
      traits<Right>();
#endif
   }

   inline value_type operator [] ( std::size_t i )            { return a*v[i] + b*w[i]; }
   inline value_type operator [] ( std::size_t i ) const      { return a*v[i] + b*w[i]; }
   inline std::size_t size () const                           { return v.size();        }

private:
   a_type a;
   V_type v;
   b_type b;
   W_type w;
};

// ============================================================== a * V
template< typename T >
class aV
{
public:
   typedef double                                      S_type;
   typedef typename array_type::value_type             value_type;
   typedef typename traits<T>::type                    V_type;

   aV ( S_type _a, const T& _v ) : a(_a), V(_v)
   {
#ifdef DUMP
      std::cout << "a*V" << std::endl;
#endif
   }

   aV ( const T& _v, S_type _a ) : a(_a), V(_v)
   {
#ifdef DUMP
      std::cout << "V*a" << std::endl;
#endif
   }

   inline value_type operator [] ( std::size_t i )            { return a*V[i];   }
   inline value_type operator [] ( std::size_t i ) const      { return a*V[i];   }
   inline std::size_t size () const                           { return V.size(); }

private:
   S_type a;
   V_type V;
};
