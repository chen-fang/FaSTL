//#include "vector_unbounded.hpp"
//#include "ADscalar.hpp"
//#include "ADvector.hpp"

#include "memory/coherent_fast.hpp"
#include <iostream>
#include <vector>

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

class A : public Base
{
public:
   int* m_data;


   A( std::size_t _size, std::size_t _value )
   {
      std::cout << "A :: ctor" << std::endl;
      m_data = new int [_size];
      std::size_t i;
      for( i = 0; i < _size; ++i )
	 m_data[i] = _value;
   }

   A( A&& other )
   {
      std::cout << "A :: move ctor" << std::endl;
      m_data = other.m_data;
      other.m_data = nullptr;
   }

   ~A()
   {
      std::cout << "A :: dtor" << std::endl;
   }
};


int main()
{
   //fastl::vector_unbounded<double>( 10 );

   //typedef fastl::coherent_fast<> ALLOC;

   std::vector<Base> vec(5);



   return -1;
}
