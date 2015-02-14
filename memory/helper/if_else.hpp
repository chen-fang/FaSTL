#pragma once


/* if-else statement with bit hacks
 *
 * Make selection without branch prediction
 * Various scenarios includes:
 * == / !=
 * >  / <=
 * <  / >=
 * 
 * Return the first argument if true; else return the second argument
 * 
 */

namespace fastl
{
   namespace detail
   {

      template< typename T1, typename T2, typename T3, typename T4 >
      inline static T3 bs_if_equal ( T1 condition1, T2 condition2,
				  T3 choice1,    T4 choice2 )
      {
	 // ( condition1 == condition2 ) ? choice1 : choice2
	 return choice2 ^ ((choice1 ^ choice2) & -(condition1 == condition2));
      }


      template< typename T1, typename T2, typename T3, typename T4 >
      inline static T3 bs_if_not_equal ( T1 condition1, T2 condition2,
				      T3 choice1,    T4 choice2 )
      {
	 // ( condition1 == condition2 ) ? choice1 : choice2
	 return choice2 ^ ((choice1 ^ choice2) & -(condition1 != condition2));
      }


      template< typename T1, typename T2, typename T3, typename T4 >
      inline static T3 bs_if_bigger ( T1 condition1, T2 condition2,
				   T3 choice1,    T4 choice2 )
      {
	 // ( condition1 > condition2 ) ? choice1 : choice2
	 return choice2 ^ ((choice1 ^ choice2) & -(condition1 > condition2));
      }


      template< typename T1, typename T2, typename T3, typename T4 >
      inline static T3 bs_if_bigger_equal ( T1 condition1, T2 condition2,
					 T3 choice1,    T4 choice2 )
      {
	 // ( condition1 >= condition2 ) ? choice1 : choice2
	 return choice2 ^ ((choice1 ^ choice2) & -(condition1 >= condition2));
      }


      template< typename T1, typename T2, typename T3, typename T4 >
      inline static T3 bs_if_smaller ( T1 condition1, T2 condition2,
				    T3 choice1,    T4 choice2 )
      {
	 // ( condition1 < condition2 ) ? choice1 : choice2
	 return choice2 ^ ((choice1 ^ choice2) & -(condition1 < condition2));
      }


      template< typename T1, typename T2, typename T3, typename T4 >
      inline static T3 bs_if_smaller_equal ( T1 condition1, T2 condition2,
					  T3 choice1,    T4 choice2 )
      {
	 // ( condition1 <= condition2 ) ? choice1 : choice2
	 return choice2 ^ ((choice1 ^ choice2) & -(condition1 <= condition2));
      }
   }
}
