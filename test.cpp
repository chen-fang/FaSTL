#include "buffer.hpp"
#include "singleton_pool.hpp"


int main()
{
   typedef fastl::singleton<32,4,8> singleton_pool;
   typedef buffer<double,singleton_pool> buffer_type;




   return -1;
}
