#pragma once

/* Level 2 
 *
 * The HYBRID version of the coherent_sequential allocator with boundary checks
 * without if-statement
 * Assumption #1: memory pool MUST be allocated successful --> p_head != nullptr
 * Assumption #2: allocated space can be exhaused s.t. boundary check is needed
 *
 */

#include <cstddef>   // provides: size_t, nullptr
#include <cstdlib>   // provides: malloc, free
#include <iostream>  // provides: cout

#include "malloc_alloc.hpp"
#include "policy/policy.h"
#include "helper_function/helper_function.hpp"

namespace fastl
{
   template< typename __Recycle = fastl :: NoRecycle,
	     std::size_t BOUNDARY = 0,
	     typename __Alloc   = fastl :: malloc_alloc,
	     typename __Align   = fastl :: Alignment<BOUNDARY> >
   class coherent : public __Alloc
   {
   public:
      coherent( std::size_t _buffer_size )
      {
	 p_head = static_cast<char*>(__Alloc :: allocate(_buffer_size));
	 p_available[0] = nullptr;
	 p_available[1] = p_head;
	 if( p_head != nullptr )
	 {
	    p_end = p_head + _buffer_size;
	 }
	 else
	 {
	    p_end = nullptr;
	    std::cout << "*******ERROR MESSAGE********"<< std::endl
		      << "coherent allocator fails" << std::endl
		      << "p_head == nullptr" <<std::endl
		      << "------------------" << std::endl
		      << "use coherent_safe for safety" << std::endl
		      << "****************************" << std::endl;
	 }
      }

      ~coherent()
      {
	 __Alloc :: deallocate( static_cast<void*>(p_head) );
      }

      inline void* allocate( std::size_t _n )
      {
	 std::size_t test_sz = fastl :: detail :: bs_if_equal( _n, 0, ALLOC_0, _n );
	 __Align :: Make_Aligned( test_sz );

	 std::size_t is_enough = ( (p_available[1] + test_sz) <= p_end ); // 2 cycles
	 void* p_ret = static_cast<void*>( p_available[ is_enough ] );

	 /* SPECIAL ASSUMPTION */
	 // p_available[1] will be incremented no matter if there is enough space
	 // Abuse of p_available[1] may cause OVERFLOW !!!
	 p_available[1] += test_sz; // 1 cycle
	 counter += is_enough;
	 return p_ret;
      }

      inline void deallocate( void* _p )
      {
	 if( _p != nullptr )
	    --counter;
	 counter.reset( p_head, p_available[1] );
      }


   private:
      char* p_head;
      char* p_available[2];
      char* p_end;
      __Recycle counter;
   };
}
