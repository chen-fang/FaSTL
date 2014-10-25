#pragma once
#include "ADscalar.hpp"

template< typename __Alloc = fastl::coherent_safe<> >
class ADvector
{
public:
   typedef __Alloc                                                   allocator_type;
   typedef typename ADscalar< allocator_type > :: size_type          size_type;
   typedef typename ADscalar< allocator_type > :: value_type         value_type;
   typedef typename ADscalar< allocator_type > :: grad_elem_type     grad_elem_type;
   typedef typename ADscalar< allocator_type > :: gradient_type      gradient_type;
   typedef fastl::vector_unbounded< value_type, allocator_type >     value_storage_type;
   typedef fastl::vector_unbounded< grad_elem_type, allocator_type > gradient_storage_type;
   typedef fastl::vector_unbounded< ADscalar< allocator_type >, allocator_type >       ADvector_type;

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
   ADvector ( size_type _size, allocator_type& _allocator, size_type _upper_bound )
      : manager      ( _size, _allocator ),
	value_storage( _size, _allocator ),
	grad_storage ( _size * _upper_bound, _allocator )
   {
      std::cout << "ADvector( size, alloc ) " << std::endl;
      std::cout << "Assigning..." << std::endl;

      std::size_t i;
      value_type* p_value = &value_storage[0];
      grad_elem_type* p_gradient = &grad_storage[0];

      for( i = 0; i < _size; ++i )
      {
	 manager[i].assign( p_value, p_gradient, _upper_bound );

	 std::cout << "------------------ " << i << std::endl;
	 std::cout << manager[i].value << std::endl;
	 std::cout << manager[i].gradient.p_begin << " ---> "
		   << manager[i].gradient.p_end   << " ---> "
		   << manager[i].gradient.p_capacity << std::endl << std::endl;

	 ++p_value;
	 p_gradient += _upper_bound;
      }
   }

   ADscalar<>& operator [] ( std::size_t index )
   {
      return manager[ index ];
   }

};
