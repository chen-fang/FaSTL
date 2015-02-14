#pragma once


template< typename X >
class ADscalarX
{
public:
   typedef double                  value_type;
   typedef X                       gradient_type;

   ADscalarX ( value_type _value, const X& _expr )
      : m_value(_value), m_gradient(_expr)
   {}

   // ADscalarX ( value_type && _value, X && _expr )
   //    : value( std::move(_value) ), expression( std::move(_expr) )
   // {}

   inline
   value_type operator [] ( std::size_t i )         {  return m_gradient[i];  }

   inline
   value_type operator [] ( std::size_t i ) const   {  return m_gradient[i];  }

   inline
   std::size_t size () const
   {
      return m_gradient.size();
   }

   inline value_type             value ()           { return m_value;    }
   inline value_type             value ()    const  { return m_value;    }
   inline gradient_type&         gradient ()        { return m_gradient; }
   inline const gradient_type&   gradient () const  { return m_gradient; }

private:
   value_type             m_value;
   gradient_type          m_gradient;
};

