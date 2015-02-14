#pragma once

#include <cmath>   // provides: log2()
#include <iostream>

/* alignment policy
 *
 * DoAlignment:
 * Modify the "requested size" if neccessary to ensure the size is
 * aligned on the "BOUNDARY"
 *
 * NoAlignment:
 * "requested size" will not be modified.
 */

//using std::log2
namespace fastl
{
   // BEGIN OF NAMESPACE
   //
   template< std::size_t BOUNDARY = alignof(double) >
   struct Alignment
   {
      constexpr static const std::size_t POWER_INDEX ()
      {
	 static_assert( BOUNDARY == ((BOUNDARY >> (int)log2(BOUNDARY)) << (int)log2(BOUNDARY)),
			"Alignment boundary MUST be the power of 2 !!!" );

	 return log2(BOUNDARY);
      }

      constexpr static std::size_t POWER = POWER_INDEX();

      // interface
      inline static void Make_Aligned ( std::size_t& _n )
      {
	 _n = ( (_n + BOUNDARY-1) >> POWER ) << POWER;
      }
   };
      




   template<>
   struct Alignment<0>
   {
      inline static void Make_Aligned ( std::size_t& _n )
      { /* do nothing */ }
   };

   // template< std::size_t BOUNDARY = alignof(double) >
   // struct NoAlignment
   // {
   //    constexpr static void Make_Aligned ( std::size_t& _n )
   //    { /* do nothing */ }
   // };
   //
   // END OF NAMESPACE
}
