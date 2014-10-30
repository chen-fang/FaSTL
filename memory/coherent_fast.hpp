#pragma once

/* Level 2
 *
 * The FAST version of the coherent_sequential allocator without any check
 * Assumption #1: construction is successful (p_head != nullptr)
 * Assumption #2: allocated space is large enough s.t. no boundary check is needed
 *
 */

#include "common_header.h"

#include "malloc_alloc.hpp"
#include "policy/policy.h"
#include "helper_function/if_else.hpp"

namespace fastl
{
   // BEGIN OF NAMESPACE
   //
   template< typename __Recycle = fastl :: NoRecycle,
	     typename __Alloc =   fastl :: malloc_alloc >
   class coherent_fast : public __Alloc
   {
   public:
      coherent_fast( std::size_t _buffer_size )
      {
	 p_head = p_available = static_cast<char*>(__Alloc :: allocate(_buffer_size));
      }

      coherent_fast ( const coherent_fast& _clone )
      {
	 std::cout << "copy ctor" << std::endl;
      }

      coherent_fast ( coherent_fast&& _other )
	 : p_head( _other.p_head ), p_available( _other.p_available ), counter( _other.counter )
      {
	 //std::cout << "co_fast :: move ctor" << std::endl;

	 _other.p_head = nullptr;
	 _other.p_available = nullptr;
	 _other.counter = 0;
      }

      ~coherent_fast()
      {
	 __Alloc :: deallocate( static_cast<void*>(p_head) );
      }

      coherent_fast& operator = ( coherent_fast&& _other )
      {

      }

      inline void* allocate( std::size_t _n )
      {
	 std::size_t test_sz = fastl :: detail :: bs_if_equal( _n, 0, ALLOC_0, _n );
	 void* p_ret = static_cast<void*>( p_available );
	 p_available +=  test_sz;
	 ++counter;
	 return p_ret;
      }

      template< std::size_t Alignment >
      inline void* allocate ( std::size_t _n )
      {
	 return __allocate ( _n, std::integral_constant<std::size_t, Alignment>() );
      }


      inline void deallocate( void* _p )
      {
	 --counter;
	 counter.reset( p_head, p_available );
      }

      inline void* front ()
      {
	 return p_head;
      }

   private:
      template< std::size_t Alignment >
      inline void* __allocate ( std::size_t _n, std::integral_constant<std::size_t, Alignment>  )
      {
	 static_assert( Alignment == ((Alignment >> (int)std::log2(Alignment))
	 			      << (int)std::log2(Alignment)),
	 		"Alignment boundary MUST be the power of 2 !!!" );

	 std::size_t test_sz = fastl :: detail :: bs_if_equal( _n, 0, ALLOC_0, _n );
	 std::size_t padding = ( p_available - p_head ) % Alignment;
	 padding = fastl :: detail :: bs_if_equal( padding, 0, 0, Alignment-padding );
	 p_available += padding;
	 void* p_ret = static_cast<void*>( p_available );
	 p_available += test_sz;
	 ++counter;
	 return p_ret;
      }

      inline void* __allocate ( std::size_t _n, std::integral_constant<std::size_t, 0> )
      {
	 return allocate(_n);
      }


      /* --- data structrue --- */
      char* p_head;
      char* p_available;
      __Recycle counter;
   };
   //
   // END OF NAMESPACE
}
