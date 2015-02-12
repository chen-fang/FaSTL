#include "freelist_pool.hpp"

int main()
{
   typedef fastl::freelist_pool<8000> ALLOC;
   ALLOC pool(1000);

   void* p;

   for( std::size_t i = 0; i < 1E06; ++i )
   {
      p = pool.allocate();
   }



   return -1;
}
