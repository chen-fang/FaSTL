#include "vector_unbounded.hpp"
#include "ADscalar.hpp"
#include "ADvector.hpp"
#include <iostream>

class A
{
public:
   A() : a(0), p(nullptr)
   {
      std::cout << "A()" << std::endl;
      std::cout << a << "\t" << p << std::endl;
   }

   A( int value ) : a(value), p(nullptr)
   {
      std::cout << "A(a)" << std::endl;
      std::cout << a << "\t" << p << std::endl;
   }

   A( int value, int* address ) : a(value), p(address)
   {
      std::cout << "A(a,p)" << std::endl;
      std::cout << a << "\t" << p << std::endl;
   }

private:
   int a;
   int* p;
};



int main()
{
   typedef fastl::coherent_safe<> ALLOC;
   ALLOC allocator( 100 * sizeof(double) );

   ADvector<> a( 4, allocator, 4 );
   //a.print();
   std::cout << a[1].get_value() << std::endl;

   return -1;
}
