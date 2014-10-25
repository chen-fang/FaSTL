#pragma once

/* Level 2
 *
 * The SAFE-RECYCLE version of the coherent_sequential allocator with boundary checks
 * using if-statement
 * Assumption #1: allocation of space could fail (p_head = NULL)
 * Assumption #2: allocated space can be exhaused s.t. boundary check is needed
 * 
 * Note #1: double deallacation causes error
 * Note #2: NoRecycle is supported, but not recommended
 * Note #3: request to allocate 0 bytes finally allocates alignof(double) bytes
 *          such that alignment is ensured 
 */

#include "common_header.h"

#include "malloc_alloc.hpp"
#include "policy/policy.h"
#include "helper_function/helper_function.hpp"

namespace fastl
{
   // BEGIN OF NAMESPACE
   //
   template< typename __Recycle = fastl :: NoRecycle,
	     typename __Alloc =   fastl :: malloc_alloc >
   class coherent_safe : public __Alloc
   {
   public:
      coherent_safe( std::size_t _buffer_size )
      {
	 p_head = p_available = static_cast<char*>(__Alloc :: allocate(_buffer_size));
	 if( p_head != nullptr )
	    p_end = p_head + _buffer_size;
	 else
	    p_end = nullptr;
      }

      ~coherent_safe()
      {
	 std::cout << "~coherent_safe()" << std::endl;
	 __Alloc :: deallocate( static_cast<void*>(p_head) );
      }

      inline void* allocate( std::size_t _n )
      {
	 std::size_t test_sz = fastl :: detail :: bs_if_equal( _n, 0, ALLOC_0, _n );
	 if( p_available != nullptr && p_available + test_sz <= p_end )
	 {
	    void* p_ret = static_cast<void*>( p_available );
	    p_available += test_sz;
	    ++counter;
	    return p_ret;
	 }
	 else
	    return nullptr;
      }

      template< std::size_t Alignment >
      inline void* allocate ( std::size_t _n )
      {
	 return __allocate( _n, std::integral_constant<std::size_t, Alignment>() );;
      }


      inline void deallocate( void* _p )
      {
	 if( _p != nullptr )
	    --counter;
	 counter.reset( p_head, p_available );
      }


   private:
      template< std::size_t Alignment >
      inline void* __allocate ( std::size_t _n, std::integral_constant<std::size_t, Alignment> )
      {
	 // static_assert( Alignment == ((Alignment >> (int)std::log2(Alignment))
	 // 			      << (int)std::log2(Alignment)),
	 // 		"Alignment boundary MUST be the power of 2 !!!" );

	 std::size_t test_sz = fastl :: detail :: bs_if_equal( _n, 0, ALLOC_0, _n );
	 std::size_t padding = ( p_available - p_head ) % Alignment;
	 padding = fastl :: detail :: bs_if_equal( padding, 0, 0, Alignment-padding );
	 if( p_available != nullptr && p_available + test_sz + padding <= p_end )
	 {
	    p_available += padding;
	    void* p_ret = static_cast<void*>( p_available );
	    p_available += test_sz;
	    ++counter;
	    return p_ret;
	 }
	 return nullptr;	 
      }


      inline void* __allocate ( std::size_t _n, std::integral_constant<std::size_t, 0> )
      {
	 return allocate(_n);
      }



      /* --- data structrue --- */
      char* p_head;
      char* p_available;
      char* p_end;
      __Recycle counter;
   };
   //
   // END OF NAMESPACE
}
