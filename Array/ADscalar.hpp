#pragma once
#include "array.hpp"
#include "ADscalarX.hpp"
#include "ADoperation.hpp"
#include "ADtraits.hpp"

class ADscalar
{
public:
   typedef double                            value_type;
   typedef fastl::array<>                    gradient_type;

   ADscalar() : m_value(0), m_gradient(4)
   {}

   ADscalar( value_type _value ) : m_value(_value), m_gradient(4)
   {}

   ADscalar( const ADscalar & _clone ) : m_value(_clone.m_value),
					m_gradient(_clone.m_gradient)
   {}

   // ADscalar( ADscalar && _other ) : m_value(_other.m_value),
   // 				    m_gradient(std::move(_other.m_gradient))
   // {}

   void make_independent ( std::size_t i )
   {
      m_gradient[i] = 1.0;
   }

   void print ()
   {
      std::cout << m_value << std::endl;
      for( std::size_t i = 0; i < 10; ++i )
	 std::cout << m_gradient[i] << "   ";
      std::cout << std::endl << std::endl;
   }

   value_type           value ()             { return m_value; }
   value_type           value ()    const    { return m_value; }
   gradient_type&       gradient ()          { return m_gradient; }
   const gradient_type& gradient () const    { return m_gradient; }

   template< typename X >
   ADscalar& operator= ( const ADscalarX<X>& _rhs )
   {
      m_value = _rhs.value();
      for( std::size_t i = 0; i < _rhs.size(); ++i )
      {
	 m_gradient[i] = _rhs[i];
      }
      return *this;
   }

private:
   value_type               m_value;
   gradient_type            m_gradient;
};
