#include "buffer.hpp"
#include "singleton_pool.hpp"

template< typename T >
void print( const T& a )
{
   for( std::size_t i = 0; i < a.size(); ++i )
   {
      std::cout << a[i] << std::endl;
   }
   std::cout << std::endl;
}

int main()
{
   typedef fastl::singleton<32,4,8> singleton_pool;
   typedef buffer<double,singleton_pool> buffer_type;

   buffer_type A(4), B(4), C(4), D(4);
   for( std::size_t i = 0; i < A.size(); ++i )
   {
      A[i] = 1.1;
      B[i] = 2.2;
      C[i] = 3.3;
      D[i] = 4.4;
   }

   std::cout << std::endl;
   std::cout << "### start from here ###" << std::endl;
   buffer_type E(4);
   std::cout << "=======================" << std::endl << std::endl;

   E = A + B + C + D;
   //E = A + ( B + (C + D) );

   print( E );



   return -1;
}
