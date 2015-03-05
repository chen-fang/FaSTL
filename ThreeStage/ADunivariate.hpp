/*
 * Created by: Chen Fang
 * Date: 03/04/2015
 */

#pragma once

#include "../Memory/memory.h"
#include "expression.hpp"

/* Forward Declaration */
// template< typename __ALLOC >
// class ADdense< __ALLOC >;

// template< typename __ALLOC >
// class ADsparse< __ALLOC >;


template< typename __ALLOC = std::malloc_alloc >
class ADunivariate
{
public:
   typedef double                         value_type;
   typedef std::size_t                    size_type;
   typedef ADunivariate<__ALLOC>          this_type;
   typedef const this_type&               const_reference_type;

   ADunivariate() : index(0), value(0.0), derivative(0.0)
   {}

   inline void make_independent( size_type i )
   {
      index = i;
   }

   /* access */
   inline value_type value() const
   {
      return m_value;
   }
   inline value_type derivative() const
   {
      return m_derivative;
   }

   inline value_type operator[] ( size_type i )
   {
      return m_derivative;
   }
   inline value_type operator[] ( size_type i ) const
   {
      return m_derivative;
   }


   /* assignment */
   ADunivariate operator= ( const_reference_type _rhs )
   {
      m_value = _rhs.value;
      m_derivative = _rhs.derivative;
   }

   template< typename Xpr >
   ADunivariate operator= ( const Xpr& _rhs )
   {
      value = _rhs.value();
   }

   /* operator */
   friend ADunivariate operator+ ( const ADunivariate& left, const ADunivariate& right );
   //friend ADdense operator+ ( const ADunivariate& left, const ADunivariate& right );
   //friend ADsparse operator+ ( const ADunivariate& _left, const ADunivariate& _right );

private:
   std::size_t m_index;
   double m_value;
   double m_derivative;
};


