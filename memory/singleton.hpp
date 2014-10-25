#include "common_header.h"

template< typename ALLOC >
class singleton
{
public:
   typedef ALLOC Alloc_t;

   static void get_instance ( std::size_t n )
   {
      if( instance == static_cast<Alloc_t*>(nullptr) )
      {
	 create(n);
      }
   }

   static void* allocate ( std::size_t n )
   {
      return instance->allocate(n);
   }

   template< std::size_t Alignment >
   static void* allocate ( std::size_t n )
   {
      return instance->allocate<Alignment>(n);
   }

private:
   static void create ( std::size_t n )
   {
      static Alloc_t Alloc(n);
      instance = &Alloc;
   }

   static Alloc_t* instance;

   // disable
   singleton() {}
   singleton( const Alloc_t& clone ) {}
   singleton( Alloc_t&& mv_cpy ) {}
   void operator= ( const Alloc_t& clone ) {}
   ~singleton() {}
};

template< typename Alloc_t >
Alloc_t* singleton<Alloc_t> :: instance = nullptr;
