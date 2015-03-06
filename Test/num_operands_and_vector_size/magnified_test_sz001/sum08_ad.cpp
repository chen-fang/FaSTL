#include "../../../Array/ADscalar.hpp"


int main()
{
   ADscalar a1, a2, a3, a4, a5, a6, a7, a8;
   ADscalar z;

   a1.make_independent(0);
   a2.make_independent(0);
   a3.make_independent(0);
   a4.make_independent(0);
   a5.make_independent(0);
   a6.make_independent(0);
   a7.make_independent(0);
   a8.make_independent(0);

   std::size_t REPEAT = 5E+09;
   for( std::size_t iter = 0; iter < REPEAT; ++iter )
   {
      /* ADscalar with expression template */
      z = a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8;
      z = a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8;
      z = a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8;
      z = a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8;
   }
   std::cout << z.value() << std::endl;
}
