#include "../../Array/ADscalar.hpp"

int main()
{
   typedef fastl::array<> array;

   array a1, a2, a3, a4, a5, a6, a7, a8;
   array z;

   std::size_t REPEAT = 2E+09;
   for( std::size_t iter = 0; iter < REPEAT; ++iter )
   {
      for( std::size_t i = 0; i < a1.size(); ++i )
      {
      	 z[i] = a1[i] + a2[i] + a3[i] + a4[i] + a5[i] + a6[i] + a7[i] + a8[i];
      }
   }
   std::cout << z[0] << std::endl;
}
