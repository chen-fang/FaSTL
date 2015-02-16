#include "ADscalar.hpp"


template< typename T >
void show ( const T& Z )
{
   for( std::size_t i = 0; i < Z.size(); ++i )
   {
      std::cout << Z[i] << "   ";
   }
   std::cout << std::endl << std::endl;
}


int main()
{
   typedef fastl::array<> array;

   array A(5), B(10), C(3);


   A = 2.5;
   show( A );

   B = 3.5;
   show( B );

   A = B;
   show( A );

   A = C;
   show( A );




}
