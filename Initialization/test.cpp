#include "construct.hpp"
#include "StopWatch.hpp"

int main()
{
   typedef double value_type;
   std::size_t Size = 100;
   std::size_t REPEAT = 10000;

   double* p = static_cast<value_type*>( std::malloc( sizeof(value_type) * Size ) );

   StopWatch my_watch;
   my_watch.begin();
   for( std::size_t i = 0; i < REPEAT; ++i )
   {
      fastl :: impl :: direct_assignment( p, Size, 1.1 );
      //fastl::CTR<value_type>::set_value( p, p+Size, 1.1 );
   }
   my_watch.stop();
   std::cout << my_watch.duration() << std::endl;
   std::cout << p[0] << "\t" << p[Size-1] << std::endl;


   std::free( static_cast<void*>(p) );


   return -1;
}
