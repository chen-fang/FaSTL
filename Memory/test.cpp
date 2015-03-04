//#include "freelist_pool.hpp"
#include "singleton_pool.hpp"


int main()
{
   typedef fastl::singleton< 4,4,sizeof(double) > singleton_pool;

   singleton_pool::allocate();
   singleton_pool::allocate();
   singleton_pool::allocate();
   singleton_pool::allocate();
   singleton_pool::allocate();
   singleton_pool::allocate();

   return -1;
}
