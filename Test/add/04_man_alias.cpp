#include "../../Array/ADscalar.hpp"

// print array
template< typename A >
void print ( const A & a )
{
   for( std::size_t i = 0; i < a.size(); ++i )
   {
      std::cout << a[i] << "   ";
   }
   std::cout << std::endl << std::endl;
}

int main()
{
   typedef fastl::array<> array;

   array A(1000), B(1000), C(1000), D(1000);
   array Z(1000);
   A[0] = 1.0;
   B[1] = 1.0;
   C[2] = 1.0;
   D[3] = 1.0;

   std::size_t REPEAT = 2000000;
   for( std::size_t j = 0; j < REPEAT; ++j )
   {
      /* Manual array operation */
      for( std::size_t i = 0; i < C.size(); ++i )
      {
      	 Z[i] = A[i] + B[i] + A[i] + B[i] ;
      }

      /* ADscalar with expression template */
      // z = a + b + c + d + e + 
      // 	 f + g + h + i + j + 
      // 	 k + l + m + n + o + 
      // 	 p + q + r + s + t ;
   }

   std::cout << Z[0] << "\t" << Z[1] << std::endl;

}
