#pragma once

#include "Op.hpp"

template< typename T >
struct VRtraits
{
   typedef T                        type;
};

template<>
struct VRtraits< ADunivariate >
{
   typedef const_reference_type     type;
};

// ==============================================================
/* Template Parameter <T>
 * int / double / std::size_t / ...
 */
template< typename T >
class Literal
{
public:
   typedef T value_type;

   Literal ( T literal ) : m_literal( literal ) {}

   inline T operator [] ( std::size_t index )
   {
      return m_literal;
   }
   
   inline T operator [] ( std::size_t index ) const
   {
      return m_literal;
   }

   inline std::size_t size () const
   {
      return 0;
   }

private:
   T m_literal;
};

// ==============================================================
/* Template Parameter <T>
 * 1). ADunivariate
 * 2). ADdense
 * 3). ADsparse
 */
template< typename T >
class Leaf
{
public:
   typedef typename T::value_type          value_type;

   Leaf ( const T& leaf ) : m_leaf( leaf ) {}

   inline value_type operator [] ( std::size_t index )
   {
      return m_leaf[index];
   }

   inline value_type operator [] ( std::size_t index ) const
   {
      return m_leaf[index];
   }

   inline std::size_t size () const
   {
      return m_leaf.size();
   }

private:
   const T& m_leaf;
};

// ==============================================================
template< typename T1, typename T2, typename Op >
class Xpr
{
public:
   typedef TRtraits< T1 >                                                  LeftType;
   typedef TRtraits< T2 >                                                  RightType;
   typedef typename T1::value_type                                         LeftValueType;
   typedef typename T2::value_type                                         RightValueType;
   typedef ValueType_Traits< LeftValueType, RightValueType >::value_type   value_type;

   Xpr ( const T1& _left, const T2& _right )
      : m_left( _left ), m_right( _right )
   {}


   // inline value_type operator [] ( std::size_t index )
   // {
   //    return Op::apply( m_left[index], m_right[index] );
   // }

   // inline value_type operator [] ( std::size_t index ) const
   // {
   //    return Op::apply( m_left[index], m_right[index] );
   // }

   inline std::size_t size () const
   {
      return m_left.size();
   }

private:
   LeftType       m_left;
   RightType      m_right;
};
