#pragma once

#include "vector.hpp"

template< typename __ALLOC = fastl::malloc_alloc >
class ADscalar
   : public __Alloc
{
public:
   typedef fastl::coherent_fast<>                                      allocator_type;
   typedef std::size_t                                                 size_type;
   typedef double                                                      value_type;
   typedef double                                                      grad_elem_type;
   typedef fastl::vector_unbounded< grad_elem_type, allocator_type >   gradient_type;

private:
   value_type*   value;
   gradient_type gradient;

public:
   ADscalar ()
      : value( static_cast<value_type*>(__ALLOC::allocate( sizeof(value_type) )) ), 
	gradient()
   {
      std::cout << "ADscalar()" << std::endl;
   }

   ADscalar ( size_type _value )
      : value( static_cast<value_type*>(__ALLOC_VALUE::allocate( sizeof(value_type) )) ), 
	gradient()
   {
      *value = _value;
   }

   ADscalar ( size_type _value, size_type _upper_bound )
      : value( static_cast<value_type*>(__ALLOC_VALUE::allocate( sizeof(value_type) )) ),
	gradient( _upper_bound )
   {
      *value = _value;
   }

   ~ADscalar()
   {
      __ALLOC :: deallocate( static_cast<void*>( value ) );
   }

   value_type get_value()
   {
      return *value;
   }

   void set_upper_bound( size_type _upper_bound )
   {
      gradient = gradient_type( _upper_bound );
   }
};
