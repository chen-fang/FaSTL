#include "../ADscalar.hpp"

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

   array A(500), B(500), C(500), D(500), E(500);
   array Z(500);
   A[0] = 1.0;
   B[1] = 1.0;
   C[2] = 1.0;
   D[3] = 1.0;
   E[4] = 1.0;


   std::size_t REPEAT = 3E+06;
   for( std::size_t iter = 0; iter < REPEAT; ++iter )
   {
      /* Manual array operation */
      for( std::size_t i = 0; i < C.size(); ++i )
      {
      	 Z[i] = A[i] + B[i] + C[i] + D[i] + E[i] 
	    + A[i] + B[i] + C[i] + D[i] + E[i]
	    + A[i] + B[i] + C[i] + D[i] + E[i];
      }
   }

   std::cout << Z[0] << "\t" << Z[999] << std::endl;
}
