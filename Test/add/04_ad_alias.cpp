#include "../../Array/ADscalar.hpp"

// print array
template< typename A >
void print ( const A & a )
{
   for( std::size_t i = 0; i < a.size(); ++i )
   {
      std::cout << a[i] << "   ";
   }
   std::cout << std::endl << std::endl;
}

int main()
{
   typedef fastl::array<> array;

   ADscalar a, b, c, d;
   ADscalar z;
   a.make_independent(0);
   b.make_independent(1);
   c.make_independent(2);
   d.make_independent(3);


   std::size_t REPEAT = 2000000;
   for( std::size_t iter = 0; iter < REPEAT; ++iter )
   {
      /* ADscalar with expression template */
      z = a + b + a + b;
   }

   std::cout << z.value() << std::endl;

}
