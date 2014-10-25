#pragma once

#include "vector_unbounded.hpp"

tempalte< typename __Alloc = fastl::coherent_safe<> >
class ADscalar
{
public:
   typedef __Alloc                                                     allocator_type;
   typedef double                                                      value_type;
   typedef double                                                      grad_elem_type;
   typedef fastl::vector_unbounded< grad_elem_type, allocator_type >   gradient_type;

private:
   value_type*   value;
   gradient_type gradient;

public:
   ADscalar ()
      : value(nullptr), gradient()
   {
      std::cout << "ADscalar()" << std::endl;
   }


   ADscalar ( double* _value, double* _gradient, std::size_t _bound )
      : value(_value), gradient(_gradient, _bound)
   {
   }

   void assign ( double* _value, double* _gradient, std::size_t _upper_bound )
   {
      value = _value;
      gradient.assign( _gradient, _upper_bound );
   }

};
