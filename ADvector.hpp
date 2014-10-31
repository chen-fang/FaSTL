#pragma once
#include "ADscalar.hpp"


typedef fastl::coherent_fast<>                      base_allocator_type;
typedef fastl::pool< base_allocator_type >          default_pool_allocator_type;


// __POOL_ALLOC must be of singleton type
template< typename __POOL_ALLOC = default_pool_allocator_type >
struct __ADvector_base
   : __POOL_ALLOC
{
   typedef __POOL_ALLOC                                allocator_type;
   typedef adetl::ADscalar< allocator_type >           ADscalar
   typedef typename ADscalar :: size_type              size_type;
   typedef typename ADscalar :: value_type             value_type;
   typedef typename ADscalar :: grad_elem_type         grad_elem_type;
   typedef typename ADscalar :: gradient_type          gradient_type;

   typedef fastl::vector< ADscalar, allocator_type >   __base_container_type;

   // This is where data is stored
   __base_container_type _data;
   base_allocator_type* _p_allocator;

   __ADvector_base ()
      : __POOL_ALLOC(), _data()
   {
   }

   __ADvector_base ( size_type _size )
      : __POOL_ALLOC( _size * ( sizeof(ADscalar) + sizeof(value_type) ) ),
	_data( _size )
   {
      _p_allocator = __POOL_ALLOC :: create_allocator ( size *
							( sizeof(ADscalar) + sizeof(value_type) ) );
   }
		 

   __ADvector_base ( size_type _size, size_type _upper_bound )
      : __POOL_ALLOC( _size * ( sizeof(ADscalar) + sizeof(value_type)
			   + _upper_bound * sizeof(grad_elem_type) ) ),
	_data( _size )
   {
      _p_allocator = __POOL_ALLOC :: create_allocator(_size *
							( sizeof(ADscalar) + sizeof(value_type) +
							  _upper_bound * sizeof(grad_elem_type) ) );
   }

   ~__ADvector_base ()
   {
      // I'm not sure whether this works or not.
      // standard layout ???
      __POOL_ALLOC :: destroy_allocator( _p_allocator );
   }

   ADscalar& operator [] ( std::size_t index )
   {
      return _data[ index ];
   }
};



class ADvector
{
public:
   

   typedef __ADvector_base<>                           container_type;
   //typedef typename ADscalar< allocator_type >                         ADscalar;
   // typedef typename ADscalar :: size_type            size_type;
   // typedef typename ADscalar :: value_type           value_type;
   // typedef typename ADscalar :: grad_elem_type       grad_elem_type;
   // typedef typename ADscalar :: gradient_type        gradient_type;

   // typedef fastl::vector< ADscalar, allocator_type > container_type;


private:
   container_type          m_Data;



public:
   ADvector ()
      : m_Data()
   {
   }

   ADvector ( size_type _size )
      : m_Data( _size )
   {}

   ADvector ( size_type _size, size_type _upper_bound )
      : m_Data( _size, _upper_bound )
   {
      size_type i;
      for( i = 0; i < _size; ++i )
      {
	 ADvector[i].set_upper_bound( _upper_bound );
      }
   }

   ~ADvector ()
   {
   }

   ADscalar<>& operator [] ( std::size_t index )
   {
      return m_Data[ index ];
   }

};
