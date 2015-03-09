//#include "expression.hpp"
#include "ADunivariate.hpp"

int main()
{
   ADuni<> A, B;
   A.make_independent(3);
   B.make_independent(3);

   ADuni<> C;
   C = A + B;
   C.Print();
   return -1;
}
