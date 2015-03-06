#include <cstddef>
#include <iostream>

int main()
{
   double a1(0.000001), a2(0.000001), a3(0.000001), a4(0.000001);
   double a5(0.000001), a6(0.000001);
   double z(0.0);

   std::size_t REPEAT = 5E+09;
   for( std::size_t iter = 0; iter < REPEAT; ++iter )
   {
      /* ADscalar with expression template */
      z += (a1 + a2 + a3 + a4 + a5 + a6);
      z += (a1 + a2 + a3 + a4 + a5 + a6);
      z += (a1 + a2 + a3 + a4 + a5 + a6);
      z += (a1 + a2 + a3 + a4 + a5 + a6);
   }

   std::cout << z << std::endl;
}
