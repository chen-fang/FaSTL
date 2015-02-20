#include "../../Array/array.hpp"
#define L1_CACHE_N (128*1024/8)     // L1 cache

int main()
{
   const std::size_t N = 10; /* number of elements for each chunk */

   typedef fastl::singleton< 30*sizeof(double) > POOL;
   typedef fastl::array<POOL> array;
   
   array A0(N,1.1), A1(N,1.1), A2(N,1.1), A3(N,1.1), A4(N,1.1);
   array A5(N,1.1), A6(N,1.1), A7(N,1.1), A8(N,1.1), A9(N,1.1);
   array LHS(N);
   
   std::size_t REPEAT = 1;//1E+07;
   for( std::size_t j = 0; j < REPEAT; ++j )
   {
      LHS = A0 + A1 + A2 + A3 + A4 + A5 + A6 + A7 + A8 + A9;
   }

   LHS.print(10);

}
