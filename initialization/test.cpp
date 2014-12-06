#include <iostream>
#include <cstddef>
#include "construct_new.hpp"
#include "StopWatch.hpp"

int main()
{
   typedef double value_type;
   //std::size_t Size = 1000000;
   std::size_t REPEAT = 1;//100000;

   // double* Base = static_cast<value_type*>( std::malloc( sizeof(value_type) * Size ) );
   // fastl::CTR<value_type>::set_zero( Base );
   // std::free( static_cast<void*>(Base) );

   std::size_t SIZE = 1;
   StopWatch my_watch;

   // Direct Assignment
   for( std::size_t i = 1; i < 6; ++i ) // 10 --> 1,000,000
   {
      SIZE *= 10;
      double* p = static_cast<value_type*>( std::malloc( sizeof(value_type) * SIZE ) );

      my_watch.begin();
      for( std::size_t r = 0; r < REPEAT; ++r )
      {
	 for( std::size_t j = 0; j < SIZE; ++j )
	 {
	    p[j] = 5.25;
	 }
      }
      my_watch.stop();
      std::cout << "1E+0"<< i << "\t" << my_watch.duration()/REPEAT << " ---> " << p[0]  << std::endl;

      std::free( static_cast<void*>(p) );
   }


   // memcpy
   std::cout << std::endl;
   std::size_t SIZE2 = 10;
   for( std::size_t i = 1; i < 6; ++i ) // 10 --> 1,000,000
   {
      SIZE2 *= 10;
      std::size_t COPY_SIZE = SIZE2 / 10;
      double* p = static_cast<value_type*>( std::malloc( sizeof(value_type) * SIZE2 ) );
      double* p_base = static_cast<value_type*>( std::malloc( sizeof(value_type) * COPY_SIZE ) );
      for( std::size_t j = 0; j < SIZE2; ++j )
      {	 p_base[j] = 5.25;  }

      
      my_watch.begin();
      for( std::size_t r = 0; r < REPEAT; ++r )
      {
	 double* p1 = p;
	 for( std::size_t k = 0; k < 10; ++k )
	 {
	    std::cout << p1 << std::endl;
	    std::memcpy( static_cast<void*>(p1), static_cast<void*>(p_base),
			 sizeof(value_type) * COPY_SIZE );
	    p1 += COPY_SIZE;
	 }
      }
      my_watch.stop();
      std::cout << "1E+0"<< i << "\t" << my_watch.duration()/REPEAT << " ---> " << p[0] << std::endl;

      std::free( static_cast<void*>(p) );
      std::cout << "here" << std::endl;
      std::free( static_cast<void*>(p_base));
      std::cout << "here2" << std::endl;
   }

   return -1;
}
