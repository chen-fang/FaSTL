#include "../../Array/array.hpp"
#define L1_CACHE_N (128*1024/8)     // L1 cache

int main()
{
   const std::size_t N = 500; /* number of elements for each chunk */
   const std::size_t INIT = L1_CACHE_N / N;

   typedef fastl::singleton< N*sizeof(double), INIT > ALLOC;
   typedef fastl::array<ALLOC> array;

   array A0(N,1.1), A1(N,1.1);
   array LHS(N);
   
   std::size_t REPEAT = 2000000;
   for( std::size_t j = 0; j < REPEAT; ++j )
   {
      LHS = A0 + A1;
   }

   LHS.print(10);
}
