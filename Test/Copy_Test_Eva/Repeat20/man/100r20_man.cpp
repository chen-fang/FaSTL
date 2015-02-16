#include "../../../ADscalar.hpp"

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

   array A(1000), B(1000), C(1000), D(1000), E(1000), F(1000), G(1000);
   array H(1000), I(1000), J(1000), K(1000), L(1000), M(1000), N(1000);
   array O(1000), P(1000), Q(1000), R(1000), S(1000), T(1000);
   array Z(1000);
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
   K[10] = 1.0;
   L[11] = 1.0;
   M[12] = 1.0;
   N[13] = 1.0;
   O[14] = 1.0;
   P[15] = 1.0;
   Q[16] = 1.0;
   R[17] = 1.0;
   S[18] = 1.0;
   T[19] = 1.0;

   ADscalar a, b, c, d, e, f, g;
   ADscalar h, i, j, k, l, m, n;
   ADscalar o, p, q, r, s, t;
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
   k.make_independent(10);
   l.make_independent(11);
   m.make_independent(12);
   n.make_independent(13);
   o.make_independent(14);
   p.make_independent(15);
   q.make_independent(16);
   r.make_independent(17);
   s.make_independent(18);
   t.make_independent(19);


   std::size_t REPEAT = 100000;
   for( std::size_t j = 0; j < REPEAT; ++j )
   {
      /* Manual array operation */
      for( std::size_t i = 0; i < C.size(); ++i )
      {
      	 Z[i] = A[i] + B[i] + C[i] + D[i] + E[i] +
      	    F[i] + G[i] + H[i] + I[i] + J[i] +
      	    K[i] + L[i] + M[i] + N[i] + O[i] +
      	    P[i] + Q[i] + R[i] + S[i] + T[i] +

	    A[i] + B[i] + C[i] + D[i] + E[i] +
      	    F[i] + G[i] + H[i] + I[i] + J[i] +
      	    K[i] + L[i] + M[i] + N[i] + O[i] +
      	    P[i] + Q[i] + R[i] + S[i] + T[i] +

	    A[i] + B[i] + C[i] + D[i] + E[i] +
      	    F[i] + G[i] + H[i] + I[i] + J[i] +
      	    K[i] + L[i] + M[i] + N[i] + O[i] +
      	    P[i] + Q[i] + R[i] + S[i] + T[i] +

	    A[i] + B[i] + C[i] + D[i] + E[i] +
      	    F[i] + G[i] + H[i] + I[i] + J[i] +
      	    K[i] + L[i] + M[i] + N[i] + O[i] +
      	    P[i] + Q[i] + R[i] + S[i] + T[i] +

	    A[i] + B[i] + C[i] + D[i] + E[i] +
      	    F[i] + G[i] + H[i] + I[i] + J[i] +
      	    K[i] + L[i] + M[i] + N[i] + O[i] +
      	    P[i] + Q[i] + R[i] + S[i] + T[i] ;/*100*/
      }

   }

   std::cout << Z[0] << "\t" << Z[999] << std::endl;
   std::cout << z.value() << std::endl;

}
