#pragma once
#include "ADscalar.hpp"

template< typename __Alloc = fastl::coherent_safe<> >
class ADvector
{
public:
   typedef __Alloc                                                   allocator_type;
   typedef std::size_t                                               size_type;
   typedef ADscalar :: value_type                                    value_type;
   typedef fastl::vector_unbounded< value_type, allocator_type >     value_storage_type;
   typedef fastl::vector_unbounded< grad_elem_type, allocator_type > gradient_type;
   typedef fastl::vector_unbounded< grad_elem_type, allocator_type > gradient_storage_type;
   typedef fastl::vector_unbounded< ADscalar, allocator_type >       ADvector_type;

   /*
    * proposed types for the future
    *
   typedef fastl::vector_unbounded< gradient_type, allocator_type >  ub_gradient_storage_type;
   typedef fastl::vector_unbounded< ADscalar, allocator_type >       ub_ADvector_type;
   typedef fastl::vector_bounded< gradient_type, allocator_type >    b_gradient_storage_type;
   typedef fastl::vector_bounded< ADscalar, allocator_type >         b_ADvector_type;
   *
   */

private:
   ADvector_type          manager;
   value_storage_type     value_storage;
   gradient_storage_type  grad_storage;

public:
   // p_capacity is obtained according to upper_bound when it is provided
   // otherwise, use __Capacity_Factor
   ADvector ( std::size_t _size, allocator_type& _allocator, size_type _upper_bound )
      : manager      ( _size, _allocator ),
	value_storage( _size, _allocator ),
	grad_storage ( _size * _upper_bound, _allocator )
   {
      std::cout << "ADvector( size, alloc ) " << std::endl;


      std::size_t i;
      for( i = 0; i < _size; ++i )
      {
	 ADvector[i].assign( double* _value, double* _grad, std::size_t _upper_bound );
	 ++_value;
	 _grad += upper_bound;
      }
   }
};
