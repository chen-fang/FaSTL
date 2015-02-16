#include "Memory/memory.h"
#include "Array/array.hpp"

	    
int main()
{
   fastl::array<> A(10,1.1), B(10,2.2), C(10);

   A.print();
   B.print();

   C = A + B;
   C.print();
   
   return -1;
}
