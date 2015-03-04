#pragma once

#include "memory.h"


/* Template Parameter
 * For freelist_pool (fix-sized):
 * --- __USER_INIT_PAPRM: initial number of chunks
 * --- __USER_GROW_PARAM: number of chunks for expansion
 * --- __USER_CHUNK_SIZE: number of bytes per chunk

 * For pool (vary-sized):
 * --- __USER_INIT_PAPRM: initial number of bytes
 * --- __USER_GROW_PARAM: number of bytes for expansion
 * --- __USER_CHUNK_SIZE: equal to 0.
 *     * Problem:
 *       1. User needs to know this detail.
 *       2. Even if user doesn't change this value, say, 500*sizeof(double),
 *          singleton_pool will work, but the type is different.
 */

namespace fastl
{
   template< std::size_t __USER_INIT_PARAM,
	     std::size_t __USER_GROW_PARAM = __USER_INIT_PARAM,
	     std::size_t __USER_CHUNK_SIZE = 500*sizeof(double),
	     typename __ALLOC = fastl::freelist_pool< __USER_CHUNK_SIZE > >
	     //fastl :: Pool< __USER_CHUNK_SIZE > >
   class singleton
   {
   public:
      typedef singleton< __USER_INIT_PARAM,
			 __USER_GROW_PARAM,
			 __USER_CHUNK_SIZE,
			 __ALLOC >             this_type;
      typedef __ALLOC                          allocator_type;

      static allocator_type& get_allocator()
      {
       	 static allocator_type pool( __USER_INIT_PARAM, __USER_GROW_PARAM );
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
