#include "../../Array/ADscalar.hpp"


int main()
{
   ADscalar a, b, c, d, e;
   ADscalar z;

   a.make_independent(0);
   b.make_independent(1);
   c.make_independent(2);
   d.make_independent(3);
   e.make_independent(4);


   std::size_t REPEAT = 1E+06;
   for( std::size_t iter = 0; iter < REPEAT; ++iter )
   {
      /* ADscalar with expression template */
      z =a + b + c + d + e + 
	 a + b + c + d + e + 
	 a + b + c + d + e + 
	 a + b + c + d + e + /*20*/

	 a + b + c + d + e + 
	 a + b + c + d + e + 
	 a + b + c + d + e + 
	 a + b + c + d + e + /*40*/

      	 a + b + c + d + e + 
	 a + b + c + d + e + 
	 a + b + c + d + e + 
	 a + b + c + d + e + /*60*/

	 a + b + c + d + e + 
	 a + b + c + d + e + 
	 a + b + c + d + e + 
	 a + b + c + d + e + /*80*/

	 a + b + c + d + e + 
	 a + b + c + d + e + 
	 a + b + c + d + e + 
	 a + b + c + d + e ; /*100*/

   }

   std::cout << z.value() << std::endl;

}
