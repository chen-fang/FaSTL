//#include "vector_unbounded.hpp"
//#include "ADscalar.hpp"
//#include "ADvector.hpp"

//#include "memory/coherent_fast.hpp"
//#include "initialization/initialization.h"
#include <iostream>
#include "vector.hpp"
#include "ADscalar.hpp"
#include "ADvector.hpp"

class Base
{
public:
   Base()
   {
      std::cout << "Base :: ctor" << std::endl;
   }

   ~Base()
   {
      std::cout << "Base :: dtor" << std::endl;
   }
};

class A
{
public:
   Base m_data;

   A() : m_data()
   {
      std::cout << "A :: ctor" << std::endl;
   }

   ~A()
   {
      std::cout << "A :: dtor" << std::endl;
      fastl :: destroy( &m_data );
   }
};


int main()
{




   //fastl::vector<double> vec( 4 );
   ADscalar<> a(111,4);
   std::cout << a.get_value() << std::endl;




   return -1;
}
