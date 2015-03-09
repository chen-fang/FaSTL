/*
 * Created by: Chen Fang
 * Date: 03/04/2015
 */

#pragma once

#include "../Memory/memory.h"
#include "array.hpp"
#include <cmath>
#include "print.hpp"

/* Forward Declaration */
// template< typename __ALLOC >
// class ADdense< __ALLOC >;

// template< typename __ALLOC >
// class ADsparse< __ALLOC >;


static std::size_t BLOCK_SIZE = 2; // force to be a power of 2
//static std::size_t BLOCK_SIZE_POWER = std::log2(BLOCK_SIZE);

template< typename __ALLOC = fastl::malloc_alloc<> >
class ADuni
{
public:
   typedef double                         value_type;
   typedef std::size_t                    size_type;
   typedef ADuni<__ALLOC>                 this_type;
   typedef const this_type&               const_reference_type;
   typedef fastl::array<__ALLOC>                 gradient_type;

   ADuni() : m_value(0.0), m_derivative(BLOCK_SIZE)
   {}

   ADuni( value_type _value ) : m_value(_value), m_derivative(BLOCK_SIZE)
   {}

   inline void make_independent( size_type _i )
   {
      m_index = _i;
      m_block_index = _i / BLOCK_SIZE;
      m_location = _i % BLOCK_SIZE;
      m_derivative[m_location] = 1.0;
   }

   /* access */
   inline size_type index() const       { return m_index;                  }
   inline size_type block_index() const { return m_block_index;            }
   inline size_type location() const    { return m_location;               }
   inline value_type value() const      { return m_value;                  }
   inline value_type derivative() const { return m_derivative[m_location]; }

   // inline value_type operator[] ( size_type i )
   // {
   //    return m_derivative;
   // }
   // inline value_type operator[] ( size_type i ) const
   // {
   //    return m_derivative;
   // }


   /* assignment */
   ADuni operator= ( const_reference_type _rhs )
   {
      m_value =       _rhs.m_value;
      m_index =       _rhs.m_index;
      m_block_index = _rhs.m_block_index;
      m_location =    _rhs.m_location;

      m_derivative[m_location] =  _rhs.derivative();
   }

   template< typename Xpr >
   ADuni operator= ( const Xpr& _rhs )
   {
      m_value = _rhs.value();
      m_index = _rhs.index();
      m_block_index = _rhs.block_index();
      m_location = _rhs.location();

      m_derivative[m_location] = _rhs.derivative();
      return *this;
   }

   /* operator */
   //friend ADuni operator+ ( const ADuni& left, const ADuni& right );
   //friend ADdense operator+ ( const ADuni& left, const ADuni& right );
   //friend ADsparse operator+ ( const ADuni& _left, const ADuni& _right );
   void Print ()
   {
      COUT( "value", m_value );
      COUT( "index", m_index );
      COUT( "derivative", derivative() );
      COUT( "block# ", m_block_index );
      COUT( "m_location", m_location );
   }

private:
   value_type        m_value;
   gradient_type     m_derivative;
   size_type         m_index;
   size_type         m_block_index;
   size_type         m_location; // index within block
};


#include "ADoperation.hpp"
