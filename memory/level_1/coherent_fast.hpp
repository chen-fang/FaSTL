#pragma once

/* 
 * Level 2
 * Coherent allocator with emphasis on performance
 * according to the following assumptions:
 * Assumption #1: construction is successful (p_head != nullptr);
 * Assumption #2: allocated size != 0;
 * Assumption #3: allocated space is large enough s.t. no boundary check is needed.
 */

#include "include_header.h"
#include "malloc_alloc.hpp"


namespace fastl
{
   // BEGIN OF NAMESPACE
   //
   template< typename __Recycle = fastl :: DoRecycle,
	     typename __Alloc =   fastl :: malloc_alloc >
   class coherent_fast : public __Alloc
   {
   public:
      coherent_fast( std::size_t _buffer_size )
      {
	 p_head = p_available = static_cast<char*>(__Alloc :: allocate(_buffer_size));
      }

      ~coherent_fast()
      {
	 __Alloc :: deallocate( static_cast<void*>(p_head) );
      }

      // Requirement: _n != 0
      inline void* allocate( std::size_t _n )
      {
	 /*
	  * if _n == 0, allocate( ALLOC_0 )

	 std::size_t test_sz = fastl :: detail :: bs_if_equal( _n, 0, ALLOC_0, _n );
	 void* p_ret = static_cast<void*>( p_available );
	 p_available +=  test_sz;
	 ++counter;
	 return p_ret;

	 */
	 char* p_ret = p_available;
	 p_available += _n;
	 ++counter;
	 return p_ret;
      }

#ifdef FASTL_SSE
      /*
       * Optimization Option
       * Allocated space will begin on the boundary of 16 required by SSE.
       */
      
      // template< std::size_t Alignment >
      // inline void* allocate ( std::size_t _n )
      // {
      // 	 return __allocate ( _n, std::integral_constant<std::size_t, Alignment>() );
      // }
#endif

#ifdef FASTL_AVX
      /*
       * Optimization Option
       * Allocated space will begin on the boundary of 32 required by AVX.
       */
#endif




      inline void deallocate( void* _p )
      {
	 if( _p != nullptr )
	 {
	    --counter;
	    counter.reset( p_head, p_available );
	 }
      }


   private:
      /* 
       * ------------Called by aligned_allocate() -----------------
       *
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
      *
      */


      char* p_head;
      char* p_available;
      __Recycle counter;
   };
   //
   // END OF NAMESPACE
}
