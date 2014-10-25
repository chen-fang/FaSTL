#pragma once

#include "vector_unbounded.hpp"

template< typename __Alloc = fastl::coherent_safe<> >
class ADscalar
{
public:
   typedef __Alloc                                                     allocator_type;
   typedef std::size_t                                                 size_type;
   typedef double                                                      value_type;
   typedef double                                                      grad_elem_type;
   typedef fastl::vector_unbounded< grad_elem_type, allocator_type >   gradient_type;

//private:
public:
   value_type*   value;
   gradient_type gradient;

public:
   ADscalar ()
      : value(nullptr), gradient()
   {
      std::cout << "ADscalar()" << std::endl;
   }

   void assign ( value_type* _p_value, grad_elem_type*  _p_gradient, size_type _upper_bound )
   {
      value = _p_value;
      gradient.assign( _p_gradient, _upper_bound );
   }

   value_type get_value()
   {
      return *value;
   }
};
