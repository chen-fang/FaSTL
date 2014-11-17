#pragma once
#include "array.h"


namespace fastl
{
class ADscalar
{
public:
   ADscalar ()
      :m_value(0), m_gradient()
   {}

   ADscalar ( double _value )
      : m_value(_value), m_gradient()
   {}

   ADscalar ( const ADscala& clone )
      : m_value( clone.value ), m_gradient( clone.gradient ) {}

   //ADscalar ( ADscalar&& rhs );

   // data access
   double value () { return m_value; }
   double value () const { return m_value; }
   array& gradient () { return m_gradient; }
   array& gradient () const { return m_gradient; }
   array& get_derivative ( std::size_t i ) { return m_gradient[i]; }
   array& get_derivative const ( std::size_t i ) { return m_gradient[i]; }

   void make_independent ( std::size_t i )
   {

   }

   void make_constant ()
   {

   }

   // operator overloading
   ADscalar operator = ( const ADscalar& _clone )
   {
      value = _clone.value;
      gradient = _clone.gradient;
   }

   // ------------------------------------------------------------- operator +
   ADscalar operator + ( const ADscalar& _left, double _value )
   {
      ADscalar tmp;
      tmp.value() = _left.value() + _value;
      tmp.gradient = _left.gradient();
      return tmp;
   }
   ADscalar operator + ( double _value, const ADscalar& _right )
   {
      ADscalar tmp;
      tmp.value() = _value + _right.value();
      tmp.gradient() = _right.gradient();
      return tmp;
   }
   ADscalar operator + ( const ADscalar& _left, const ADscalar& _right )
   {
      ADscalar tmp;
      tmp.value() = _left.value() + _right.value();
      tmp.gradient() = _left.gradient() + _right.gradient(); // move
      return tmp;
   }

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

   // ------------------------------------------------------------- operator

private:
   double m_value;
   array m_gradient;
};


