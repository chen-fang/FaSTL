#include "Array/array.hpp"
// #include <iostream>
// #include <cstddef>
// #include <cstdlib>
// #include "Memory/pool.hpp"

int main()
{
   typedef fastl::Pool<> ALLOC;
   ALLOC alloc(32);


   // fastl::RecycleManager<> R;

   // R.initialize();
   // R.print();

   // R.update( 32 );
   // //R.print();

   // R.update( 1024 );
   // //R.print();




   // char** p = static_cast<char**>( std::malloc( 16 ) );
   // std::cout << (void**)( p ) << std::endl;
   // std::cout << (void**)( p+1 ) << std::endl;

   // std::cout << &p[0] << std::endl;
   // std::cout << &p[1] << std::endl;

   // std::free( p );

   return -1;
}


