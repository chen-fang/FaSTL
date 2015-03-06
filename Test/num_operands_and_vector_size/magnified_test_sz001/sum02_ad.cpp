#include "../../../Array/ADscalar.hpp"


int main()
{
   ADscalar a1, a2;
   ADscalar z;

   a1.make_independent(0);
   a2.make_independent(0);

   std::size_t REPEAT = 5E+09;
   for( std::size_t iter = 0; iter < REPEAT; ++iter )
   {
      /* ADscalar with expression template */
      z = a1 + a2;
      z = a1 + a2;
      z = a1 + a2;
      z = a1 + a2;
   }

   std::cout << z.value() << std::endl;

}
