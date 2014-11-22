#pragma once
#include "buffer.hpp"
#include "singleton_pool.hpp"
#include "operation.hpp"

namespace fastl
{
class ADscalar
{
public:
   static std::size_t INIT = 100;
   typedef fastl :: singleton_pool< sizeof(double*), INIT > ALLOC_V;
   typedef fastl :: singleton_pool< INIT * sizeof(double*), INIT > ALLOC_G;

   typedef double value_type;
   typedef fastl :: buffer< value_type, ALLOC_G > gradient_type;
  
public:
   ADscalar ()
      :m_value(nullptr),
       m_gradient()
   {}

   ADscalar ( double _value )
      : m_value( static_cast< value_type* >( ALLOC_V :: allocate() ) ),
	m_gradient()
   {
      *(m_value) = _value;
   }

   ADscalar ( double _value, const gradient_type& _grad )
      : m_value( static_cast< value_type* >( ALLOC_V :: allocate() ) ),
	m_gradient( _grad )
   {
      *(m_value) = _value;
   }

   ADscalar ( const ADscala& _clone )
      : m_value( static_cast< value_type* >( ALLOC_V :: allocate() ) ),
	m_gradient( _clone.m_gradient )
   {
      *(m_value) = *(_clone.value);
   }

   ADscalar ( ADscalar&& _other )
      : m_value( _other.m_value ),
	m_gradient( std::move( _clone.m_gradient ) )
   {
      _other.m_value = nullptr;
   }

   // Assignment
   ADscalar& operator = ( const ADscalar& _clone );
   ADscalar& operator = ( ADscalar&& _clone );

   // data access
   double value () { return *m_value; }
   double value () const { return *m_value; }
   gradient_type& gradient () { return m_gradient; }
   gradient_type& gradient () const { return m_gradient; }
   value_type& derivative ( std::size_t i ) { return m_gradient[i]; }
   value_type  derivative ( std::size_t i ) const { return m_gradient[i]; }

   void make_independent ( std::size_t i )
   {
      this -> derivative(i) = 1.0;
   }

   void make_constant ()
   {

   }


   



private:
   value_type*    m_value;
   gradient_type  m_gradient;
};

   
   // ------------------------------------------------------------- operator =
   ADscalar& ADscalar :: operator = ( const ADscalar& _clone )
   {
      this->value() = _clone.value();
      this->gradient() = _clone.gradient();
      return *this;
   }

   ADscalar& ADscalar :: operator = ( ADscalar&& _other )
   {
      value_type* ptr = m_value;
      
      m_value = _other.m_value;
      m_gradient = std::move( _clone.m_gradient );

      _other.value = ptr;
   }

   // ------------------------------------------------------------- operator +
   ADscalar operator + ( double _value, const ADscalar& _ad )
   {
      return ADscalar( _value + _ad.value(), _ad.gradient() );
   }

   ADscalar operator + ( const ADscalar& _ad, double _value )
   {
      return ( _value + _ad );
   }

   ADscalar operator + ( const ADscalar& _ad1, const ADscalar& _ad2 )
   {
      retrun ADscalar( _ad1.value() + _ad2.value(),
		       _ad1.gradient() + _ad2.gradient() );
   }

   // ------------------------------------------------------------- operator *
   ADscalar operator * ( double _value, const ADscalar& _ad )
   {
      return ADscalar( _value * _ad.value(), stv( _value, _ad ) );
   }

   ADscalar operator * ( const ADscalar& _ad, double _value )
   {
      return ( _value * _ad );
   }

   ADscalar operator * ( const ADscalar& _ad1, const ADscalar& _ad2 )
   {
      return ADscalar( _ad1.value() * _ad2.value(),
		       stvpstv( _ad1.value(), _ad2.gradient(), _ad2.value(), _ad1.gradient() );
   }

