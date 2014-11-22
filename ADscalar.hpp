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
      *m_value = _value;
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

   // operator overloading
   ADscalar& operator = ( const ADscalar& _clone );
   ADscalar& operator = ( ADscalar&& _clone );
   
   friend ADscalar operator + ( const ADscalar& _ad, double _value );
   friend ADscalar operator + ( double _value, const ADscalar& _ad );

   // ------------------------------------------------------------- operator '+='/'-='/'*=' /'/='
   // +=
   ADscalar& operator += ( double _value )
   {
      m_value += _value;
      return *this;
   }
   ADscalar& operator += ( const ADscalar& _rhs )
   {
      m_value += _rhs.value();
      m_gradient += _rhs.gradient();
      return *this;
   }
   // -=
   ADscalar& operator -= ( double _value )
   {
      m_value -= _value;
      return *this;
   }
   ADscalar& operator -= ( const ADscalar& _rhs )
   {
      m_value -= _rhs.value();
      m_gradient -= _rhs.gradient();
      return *this;
   }
   // *=
   ADscalar& operator *= ( double _value )
   {
      m_value *= _value;
      m_gradient *= _value;
      return *this;
   }
   ADscalar& operator *= ( const ADscalar& _rhs )
   {
      double v = m_value;
      m_value *= _rhs.value();
      m_gradient = v * _rhs.gradient() + _rhs.value() * m_gradient();
      return *this;
   }
   ADscalar& operator /= ( double _value )
   {
      m_value /= _value;
      return *this;
   }
   ADscalar& operator /= ( const ADscalar& _rhs )
   {

   }


private:
   value_type*    m_value;
   gradient_type  m_gradient;
};




   
   // ------------------------------------------------------------- operator =
   ADscalar& ADscalar :: operator = ( const ADscalar& _clone )
   {
      *(m_value) = *( _clone.value );
      m_gradient = _clone.m_gradient;
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
   ADscalar& ADscalar :: operator + ( double _value )
   {
      m_value += _value;
      return *this;
   }

   ADscalar& ADscalar :: operator + ( const ADscalar& _other )
   {
      m_value += _other.m_value;
      tmp.gradient() = _left.gradient() + _right.gradient(); // move
      return tmp;
   }

   // ------------------------------------------------------------- operator '+='/'-='/'*=' /'/='
   // +=
   ADscalar& ADscalar :: operator += ( double _value )
   {
      m_value += _value;
      return *this;
   }
   ADscalar& ADscalar :: operator += ( const ADscalar& _rhs )
   {
      m_value += _rhs.value();
      m_gradient += _rhs.gradient();
      return *this;
   }
   // -=
   ADscalar& ADscalar :: operator -= ( double _value )
   {
      m_value -= _value;
      return *this;
   }
   ADscalar& ADscalar :: operator -= ( const ADscalar& _rhs )
   {
      m_value -= _rhs.value();
      m_gradient -= _rhs.gradient();
      return *this;
   }
   // *=
   ADscalar& ADscalar :: operator *= ( double _value )
   {
      m_value *= _value;
      m_gradient *= _value;
      return *this;
   }
   ADscalar& ADscalar :: operator *= ( const ADscalar& _rhs )
   {
      double v = m_value;
      m_value *= _rhs.value();
      m_gradient = v * _rhs.gradient() + _rhs.value() * m_gradient();
      return *this;
   }
   ADscalar& ADscalar :: operator /= ( double _value )
   {
      m_value /= _value;
      return *this;
   }
   ADscalar& ADscalar :: operator /= ( const ADscalar& _rhs )
   {

   }
