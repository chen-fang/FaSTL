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
   // typedef fastl::array<> array;

   // array A(1000), B(1000), C(1000), D(1000), E(1000);
   // array Z(1000);
   // A[0] = 1.0;
   // B[1] = 1.0;
   // C[2] = 1.0;
   // D[3] = 1.0;
   // E[4] = 1.0;

   ADscalar a, b, c, d, e;
   ADscalar z;
   a.make_independent(0);
   b.make_independent(1);
   c.make_independent(2);
   d.make_independent(3);
   e.make_independent(4);


   std::size_t REPEAT = 3E+06;
   for( std::size_t iter = 0; iter < REPEAT; ++iter )
   {
      /* Manual array operation */
      // for( std::size_t i = 0; i < C.size(); ++i )
      // {
      // 	 Z[i] = A[i] + B[i] + C[i] + D[i] + E[i] ;
      // }

      /* ADscalar with expression template */
      z = a + b + c + d + e
	 +a + b + c + d + e
	 +a + b + c + d + e
	 +a + b + c + d + e;
   }

   // std::cout << Z[0] << "\t" << Z[999] << std::endl;
   std::cout << z.value() << std::endl;

}
