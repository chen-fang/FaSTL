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

   array A(2), B(2), C(2), D(2), E(2), F(2), G(2);
   array H(2), I(2), J(2);
   array Z(2);
   A[0] = 1.0;
   B[0] = 1.0;
   C[0] = 1.0;
   D[0] = 1.0;
   E[0] = 1.0;
   F[0] = 1.0;
   G[0] = 1.0;
   H[0] = 1.0;
   I[0] = 1.0;
   J[0] = 1.0;

   ADscalar a, b, c, d, e, f, g;
   ADscalar h, i, j;
   ADscalar z;
   a.make_independent(0);
   b.make_independent(0);
   c.make_independent(0);
   d.make_independent(0);
   e.make_independent(0);
   f.make_independent(0);
   g.make_independent(0);
   h.make_independent(0);   
   i.make_independent(0);
   j.make_independent(0);


   std::size_t REPEAT = 5e+09;
   for( std::size_t iter = 0; iter < REPEAT; ++iter )
   {
      /* ADscalar with expression template */
      z = a + b + c + d + e + f ;
   }

   std::cout << Z[0] << std::endl;
   std::cout << z.value() << std::endl;

}
