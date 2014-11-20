#pragma once

#include "common_header.h"
#include "freelist_pool.hpp"


namespace fastl
{
   template< std::size_t __RequestSize,
	     std::size_t __InitSize,
	     std::size_t __GrowSize,
	     typename __Alloc = fastl :: coherent_freelist< __RequestSize > >
   class singleton
   {
   private:
      typedef fastl::singleton<__RequestSize,__InitSize,__GrowSize,__Alloc> this_type;
      typedef __Alloc allocator_type;

      /*
       * Explicit call to the following functions
       * is prohibited.
       */
      singleton();
      singleton( const this_type& clone );
      singleton( this_type&& rhs );
      singleton operator = ( const this_type& clone );
      singleton operator = ( this_type&& rhs );
      ~singleton();
      
   public:

      static void* allocate ()
      {
	 allocator_type& alloc = get_allocator();
	 return alloc.allocate();
      }

      static void deallocate ( void* _p )
      {
	 allocator_type& alloc = get_allocator();
	 alloc.deallocate( _p );
      }

   private:
      static allocator_type& get_allocator()
      {
	 // static bool is_first_time = true;
	 // if( is_first_time )
	 // {
	 //    static allocator_type pool( __InitSize, __GrowSize );
	 //    is_first_time = false;
	 // }

	 static allocator_type pool( __InitSize, __GrowSize );
	 return pool;
      }
   };
}
