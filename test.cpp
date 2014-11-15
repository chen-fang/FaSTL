#include "coherent_freelist.hpp"



int main()
{
   typedef fastl::coherent_freelist<4> freelist;
   freelist list( 4, 2 );

   void* p1 = list.allocate();
   void* p2 = list.allocate();
   void* p3 = list.allocate();
   void* p4 = list.allocate();

   void* pp1 = list.allocate();
   list.deallocate( p1 );
   p1 = list.allocate();

   return -1;
}
