#pragma once

#include <cstddef> // provides size_t
#include "memory/memory.h"
#include "initialization/initiliazation.h"

namespace fastl
{
   template< typename __T,
	     typename __Alloc = fastl::malloc_alloc >
   class vector
      : public __Alloc
   {
      
   protected:
      typedef vector                            this_type;
      typedef fastl::mpl::type_traits< vector > type_traits;
   public:
      typedef typename type_traits::value_type                value_type;
      typedef typename type_traits::pointer                   pointer;
      typedef typename type_traits::const_pointer             const_pointer;
      typedef typename type_traits::reference                 reference;
      typedef typename type_traits::const_reference           const_reference;
      typedef typename type_traits::elem_param_type           elem_param_type;
      typedef typename type_traits::elem_const_param          elem_const_param;

      typedef typename type_traits::size_type                 size_type;
      typedef typename type_traits::difference_type           difference_type;
      typedef typename type_traits::iterator                  iterator;
      typedef typename type_traits::const_iterator            const_iterator;
      typedef typename type_traits::param_type                param_type;
      typedef typename type_traits::const_param               const_param;

   private:
      pointer         p_bob; // beginning of buffer
      pointer         p_eob; // end of buffer
      pointer         p_eos; // end of size

   public:
      //.............................  LIFECYCLE  ..........................//

      vector ()
	 : __Alloc(), p_bob(nullptr), p_eob(nullptr), p_eos(nullptr)
      {}

      vector ( size_type _size, size_type _capacity = _size )
	 : __Alloc( _capacity * sizeof(value_type) )
      {
	 p_bob = static_cast< value_type* >( __Alloc::allocate( _capacity ) );
	 p_eos = p_bob + _size;
	 p_eob = p_bob + _capacity;
	 fastl::construct( p_bob, p_eob );
	 set_zero();
      }

      vector ( size_type _size, value_type _value, size_type _capacity = _size )
	 : __Alloc( _capacity * sizeof(value_type) )
      {
	 if( _capacity < _size )
	    _capacity = _size;
	 p_bob = static_cast< value_type* >( __Alloc::allocate( _size ) );
	 p_eos = p_bob + _size;
	 p_eob = p_bob + _capacity;
	 fastl::construct( p_bob, p_eob, _value );
      }
      
      vector ( const_param _clone )
	 : __Alloc( _clone.capacity() )
      {
	 copy_from( _clone );
      }

     vector ( vector&& _other )
	: p_bob(nullptr), p_eob(nullptr), p_eos(nullptr)
     {
	std::cout << "vector :: move constructor" << std::endl;

	p_bob = _other.p_bob;
	p_eob = _other.p_eob;
	p_eos = _other.p_eos;

	_other.p_bob = nullptr;
	_other.p_eob = nullptr;
	_other.p_eos = nullptr;
     }

      vector& operator = ( const vector& _clone )
      {
	 std::cout << "vector :: copy assignment" << std::endl;

	 if( this != &_clone )
	 {
	    copy_from( _clone );
	 }
      	 return *this;
      }

      vector& operator = ( vector&& _other )
      {
	 std::cout << "vector :: move assignment" << std::endl;

	 if( this != &_other )
	 {
	    __Alloc::deallocate( p_bob );

	    p_bob = _other.p_bob;
	    p_eob = _other.p_eob;
	    p_eos = _other.p_eos;

	    _other.p_bob = nullptr;
	    _other.p_eob = nullptr;
	    _other.p_eos = nullptr;
	 }
	 return *this;
      }

      ~vector ()
      {
	 fastl :: destroy_array( p_bob, p_eob );
	 __Alloc :: deallocate( p_bob );
      }

   private:
      void copy_from( const vector& _clone )
      {
	 const size_type clone_capacity = _clone.capacity();
	 const size_type clone_size = _clone.size();

	 p_bob = static_cast< value_type* >( __Alloc::allocate(clone_capacity) );
	 if( p_bob == nullptr )
	 {
	    std::cout << "vector :: get nullptr from allocator...!!!" << std::endl;
	    p_eob = p_bob = nullptr;
	 }
	 else
	 {
	    p_eob = p_bob + clone_capacity;
	    p_eos = p_bob + clone_size;
	    fastl::uninitialized_copy(xx,xx,xx);
	 }
      }
   
      //...........................  ASSIGNMENT  ..........................//
      
      param_type operator= ( const_param _v_rhs );

      param_type operator= ( elem_const_param _s_rhs );
      
      //.............................  ACCESS  ............................//

      bool             is_empty ( ) const;
      bool             is_full ( ) const;
      size_type        size  ( ) const;
      size_type        capacity ( ) const;

      const_iterator   begin ( ) const;
      const_iterator   end   ( ) const;
      elem_const_param front ( ) const;
      elem_const_param back  ( ) const;      
      elem_const_param operator[] ( size_type _i ) const;

      void             set_zero ( );
      void             reserve ( size_type _n );
	  void			   clear_reserve ( size_type _n );
      void             clear ( );
      void             resize ( size_type _n );
	  void			   resize ( size_type _n, elem_const_param _val );
	  void             resize_NC ( size_type _n );
      void             push_back ( elem_const_param _s );
	  void			   push_back_NC( elem_const_param _v );

	  void			   expand_vector ( );
	  void			   increment_size ( ) { ++p_eos; }

      iterator         begin ( );
      iterator         end   ( );
      elem_param_type  front ( );
      elem_param_type  back  ( );      
      elem_param_type  operator[] ( size_type _i );

      //.............................  OPERATORS  .........................//
   
      bool operator== ( const_param _v_rhs );
      
   protected:
      // Capacity growth policy parameters
      // TODO These are arbitrary for now
      static size_type GROWTH_FACTOR;
      static size_type MIN_GROW; 
      static size_type MAX_GROW;

      // resize buffer without necessarily re-copying data to new location
      void resize_buffer ( size_type _n );

   
   }


}

