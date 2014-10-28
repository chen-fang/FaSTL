#pragma once

#include <cstddef> // provides size_t
#include "memory/memory.h"
#include "initialization/initialization.h"


namespace fastl
{
   template< typename __T,
	     typename __Alloc = fastl::coherent_safe<>,
	     std::size_t __Capacity_Factor = 1 >
   class vector_unbounded
   {
   public:
      typedef __T value_type;
      typedef __Alloc allocator_type;
      typedef std::size_t size_type;

      //private:
   public:
      __T* p_begin;
      __T* p_end;
      __T* p_capacity;
     __allocator_type* p_alloc;

   public:
      vector_unbounded ()
	 : p_begin(nullptr), p_end(nullptr), p_capacity(nullptr), p_alloc(nullptr)
      {
	 std::cout << "vector_unbounded()" << std::endl;
      }

      vector_unbounded ( std::size_t _size, __Alloc& _allocator )
      {
	 std::cout << "vector_unbounded( size, alloc )" << std::endl;
	 vector_unbounded_allocate( _size, _allocator );
	 fastl :: construct_array( p_begin, p_capacity );
	 fastl :: set_zero( p_begin, p_capacity );
      }


      // template< typename T1, typename... Args >
      // vector_unbounded ( std::size_t _size, __Alloc& _allocator, T1&& _arg1, Args&&... _args )
      // {
      // 	 vector_unbounded_allocate( _size, _allocator );
      // 	 fastl :: construct_array( p_begin, p_capacity,
      // 				   std::forward<T1>( _arg1 ),
      // 				   std::forward<Args...>(_args)... );
      // }
      
      // vector_unbounded ( const_param _clone );

      ~vector_unbounded ( ) {}

      inline void assign ( __T* _p, std::size_t _range )
      {
      	 p_begin = _p;
      	 p_end = p_capacity = _p + _range;
      }

      __T& operator [] ( std::size_t index )
      {
	 return *( p_begin + index );
      }








      void print ()
      {
      	 std::cout << "vector_unbounded: "<< p_begin <<" --> "
		   << p_end << " --> " << p_capacity << std::endl;
      }

   private:
      void vector_unbounded_allocate ( std::size_t _size, __Alloc& _allocator )
      {
	 p_begin = static_cast<__T*>( _allocator.allocate( _size * sizeof(__T) ) );
	 p_end = p_begin + _size;
	 p_capacity = p_begin + _size * __Capacity_Factor;
	 p_alloc = &_allocator;
      }



   
   //    //...........................  ASSIGNMENT  ..........................//
      
   //    param_type operator= ( const_param _v_rhs );

   //    template< typename _T >
   //    param_type operator= ( const adetl::ADvector_T<_T> &_rhs );

   //    //param_type operator*= ( double_t _c );

   //    param_type operator= ( elem_const_param _s_rhs );
      
   //    //.............................  ACCESS  ............................//

      bool is_empty () const
      {
	 return ( p_begin == p_end );
      }

      bool is_full () const;
      {
	 return ( p_end == p_capacity );
      }

      size_type size () const
      {
	 return static_cast< size_type >( p_end - p_begin );
      }

      size_type capacity () const
      {
	 return static_cast< size_type >( p_capacity - p_begin );
      }


   //    const_iterator   begin ( ) const;
   //    const_iterator   end   ( ) const;
   //    elem_const_param front ( ) const;
   //    elem_const_param back  ( ) const;      
   //    elem_const_param operator[] ( size_type _i ) const;
      
   //    void			   clear_memory ( );
   
      inline void set_zero ()
      {
	 fastl::set_zero( p_begin, p_capacity );
      }

      inline void resize ( allocator_type& _allocator )
      {

      }

      inline void reserve ( size_type _size )
      {

      }
   //    void             reserve ( size_type _n );
   //    void			   clear_reserve ( size_type _n );
   //    void             clear ( );
   //    void             resize ( size_type _n );
   //    void             resize_NC ( size_type _n );
      
   //    void             push_back ( elem_const_param _s );
   //    void			   push_back_NC( elem_const_param _v );
      
   //    void			   expand_vector ( );
   //    void			   increment_size ( ) { ++p_eos; }
      
   //    iterator         begin ( );
   //    iterator         end   ( );
   //    elem_param_type  front ( );
   //    elem_param_type  back  ( );      
   //    elem_param_type  operator[] ( size_type _i );

   //    // static void set_growth_param ( size_type _GROWTH_FACTOR, size_type _MIN_GROW )
   //    // {
   //    // 	 GROWTH_FACTOR = _GROWTH_FACTOR;
   //    // 	 MIN_GROW = _MIN_GROW;
   //    // }

   //    //.............................  OPERATORS  .........................//
   
   //    bool operator== ( const_param _v_rhs );
      
   // // protected:
   // //    // Capacity growth policy parameters
   // //    // TODO These are arbitrary for now
   // //    static size_type GROWTH_FACTOR;
   // //    static size_type MIN_GROW; 
   // //    // static size_type MAX_GROW;

   //    // resize buffer without necessarily re-copying data to new location
   //    void			   resize_buffer ( size_type _n );


   // };


};



