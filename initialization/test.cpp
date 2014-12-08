#include "construct.hpp"
#include "StopWatch.hpp"

int main()
{
   typedef double value_type;
   std::size_t Size = 22;
   //std::size_t REPEAT = 1;//100000;

   double* p = static_cast<value_type*>( std::malloc( sizeof(value_type) * Size ) );

   std::cout << p << " -----" << p+Size << std::endl << std::endl;
   fastl::CTR<value_type>::set_value( p, p+Size, 1.1 );

   for( std::size_t i = 0; i < Size; ++i )
      std::cout << i << "\t" << p[i] << std::endl;

   std::free( static_cast<void*>(p) );


   return -1;
}
