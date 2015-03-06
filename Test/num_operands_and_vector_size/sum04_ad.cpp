#include "../../Array/ADscalar.hpp"


int main()
{
   ADscalar a1, a2, a3, a4;
   ADscalar z;

   a1.make_independent(0);
   a2.make_independent(0);
   a3.make_independent(0);
   a4.make_independent(0);

   std::size_t REPEAT = 2E+09;
   for( std::size_t iter = 0; iter < REPEAT; ++iter )
   {
      /* ADscalar with expression template */
      z = a1 + a2 + a3 + a4;
   }

   std::cout << z.value() << std::endl;

}
