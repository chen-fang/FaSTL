#include "freelist_pool.hpp"

int main()
{
   typedef fastl::freelist_pool<16> ALLOC;
   ALLOC pool(4);


   void* p1 = pool.allocate();
   void* p2 = pool.allocate();
   void* p3 = pool.allocate();
   void* p4 = pool.allocate();
   void* p5 = pool.allocate();

   pool.deallocate( p1 );
   pool.deallocate( p3 );
   pool.deallocate( p5 );

   p1 = pool.allocate();
   p3 = pool.allocate();
   p5 = pool.allocate();



   p1 = nullptr;



   return -1;
}
