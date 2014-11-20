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

#include "include_header.h"
#include "malloc_alloc.hpp"

namespace fastl
{
   // BEGIN OF NAMESPACE
   //
   template< typename __Recycle = fastl :: DoRecycle,
	     typename __Alloc =   fastl :: malloc_alloc >
   class coherent_safe : public __Alloc
   {
   public:
      coherent_safe( std::size_t _buffer_size )
      {
	 expand( _buffer_size );
      }

      ~coherent_safe()
      {
	 __Alloc :: deallocate( static_cast<void*>(p_head) );
      }

      /* 
       * Important Note:
       * allocate(0) is supported for specific purpose.
       * It returns "p_available" without the need to implement an extra function
       * which exposes inner data structure of ths allocator.
       * But the returned pointer should NEVER be used~!!!
       *
       * Possible application: vector.resize( n )
       * If vector.p_end () == static_cast<T*>( ALLOC::allocate(0) ), expand
       * without assigning a new allocator to the vector.
       */
      inline void* allocate( std::size_t _n )
      {
	 if( _n == 0 )
	    return p_available;

	 if( p_available != nullptr && p_available + _n <= p_end )
	 {
	    void* p_ret = static_cast<void*>( p_available );
	    p_available += _n;
	    ++counter;
	    return p_ret;
	 }
	 return nullptr;

	 /* // strategy to ( _n = 0 )

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

	 */
      }

#ifdef FASTL_SSE
#endif

#ifdef FASTL_AVX
#endif


   protected:
      char* expand ( std::size_t _grow_size )
      {
	 p_head = p_available = static_cast<char*>(__Alloc :: allocate(_grow_size))
;
	 if( p_head != nullptr )
	    p_end = p_head + _buffer_size;
	 else
	    p_end = nullptr;

	 return p_head;
      }

   private:
      char*        p_head;
      char*        p_available;
      char*        p_end;
      __Recycle    counter;
   };
   //
   // END OF NAMESPACE
}
