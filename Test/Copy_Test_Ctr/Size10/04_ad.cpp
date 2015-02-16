#include "../../ADscalar.hpp"

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

   array A(10), B(10), C(10), D(10), E(10), F(10), G(10);
   array H(10), I(10), J(10);
   array Z(10);
   A[0] = 1.0;
   B[1] = 1.0;
   C[2] = 1.0;
   D[3] = 1.0;
   E[4] = 1.0;
   F[5] = 1.0;
   G[6] = 1.0;
   H[7] = 1.0;
   I[8] = 1.0;
   J[9] = 1.0;

   ADscalar a, b, c, d, e, f, g;
   ADscalar h, i, j;
   ADscalar z;
   a.make_independent(0);
   b.make_independent(1);
   c.make_independent(2);
   d.make_independent(3);
   e.make_independent(4);
   f.make_independent(5);
   g.make_independent(6);
   h.make_independent(7);   
   i.make_independent(8);
   j.make_independent(9);


   std::size_t REPEAT = 1e+09;
   for( std::size_t iter = 0; iter < REPEAT; ++iter )
   {
      /* ADscalar with expression template */
      z = a + b + c + d;
   }

   std::cout << Z[0] << std::endl;
   std::cout << z.value() << std::endl;

}
