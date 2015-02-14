#pragma once

//#include "common_header.h"
#include "freelist_pool.hpp"


namespace fastl
{
   template< std::size_t __USER_CHUNK_SIZE,
	     std::size_t __USER_INIT_N_CHUNK = 25,
	     std::size_t __USER_GROW_N_CHUNK = __USER_INIT_N_CHUNK,
	     typename __ALLOC = fastl :: freelist_pool< __USER_CHUNK_SIZE > >
   class singleton
   {
   public:
      typedef singleton< __USER_CHUNK_SIZE,
			 __USER_INIT_N_CHUNK,
			 __USER_GROW_N_CHUNK,
			 __ALLOC >                   this_type;
      typedef __ALLOC                                allocator_type;

      static allocator_type& get_allocator()
      {
       	 static allocator_type pool( __USER_INIT_N_CHUNK, __USER_GROW_N_CHUNK );
 	 return pool;
      }

      
   public:
      static void* allocate ()
      {
	 allocator_type& allocator = get_allocator();
	 return allocator.allocate();
      }

      static void* allocate ( std::size_t _alloc_size )
      {
	 allocator_type& allocator = get_allocator();
	 return allocator.allocate( _alloc_size );
      }

      static void deallocate ( void* _p_dealloc )
      {
	 allocator_type& allocator = get_allocator();
	 allocator.deallocate( _p_dealloc );
      }

   private:
      /* Disable ctors & dtors explicitly */
      singleton();
      singleton( const this_type& clone );
      singleton( this_type&& rhs );
      singleton operator = ( const this_type& clone );
      singleton operator = ( this_type&& rhs );
      ~singleton();
   };
}
