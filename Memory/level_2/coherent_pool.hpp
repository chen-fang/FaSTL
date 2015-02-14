#pragma once

/* Level 2
 */


namespace fastl
{
   // BEGIN OF NAMESPACE
   //
   template< typename __Recycle = fastl :: DoRecycle,
	     typename __Alloc =   fastl :: malloc_alloc >
   class coherent_pool : public __Alloc
   {
   public:
      coherent_pool ( std::size_t _init_size )
	 : InitSize(_init_size), GrowSize(_init_size),
	   p_head(nullptr), p_available(nullptr), p_end(nullptr)
      {
	 p_head = expand( _init_size );
      }

      ~coherent_pool ()
      {
	 __Alloc :: deallocate( static_cast<void*>(p_head) );
      }

      /* 
       * Important Note:
       * allocate(0) is supported for specific purpose.
       * It returns "p_available" without the need to implement an extra function
       * which exposes inner data structure of ths allocator.
       * But the returned pointer should NEVER be used~!!!
       *
       * Possible application: vector.resize( n )
       * If vector.p_end () == static_cast<T*>( ALLOC::allocate(0) ), expand
       * without assigning a new allocator to the vector.
       */
      inline void* allocate( std::size_t _n )
      {
	 if( _n == 0 || p_available == nullptr )
	    return p_available;

	 if( p_available + _n <= p_end )
	 {
	    void* p_ret = static_cast<void*>( p_available );
	    p_available += _n;
	    ++counter;
	    return p_ret;
	 }

	 if( GrowSize < _n )
	    GrowSize += _n;
	    
	 expand( GrowSize );
	 
	 
	 return nullptr;

	 /* // strategy to ( _n = 0 )

	 std::size_t test_sz = fastl :: detail :: bs_if_equal( _n, 0, ALLOC_0, _n );
	 if( p_available != nullptr && p_available + test_sz <= p_end )
	 {
	    void* p_ret = static_cast<void*>( p_available );
	    p_available += test_sz;
	    ++counter;
	    return p_ret;
	 }
	 else
	    return nullptr;

	 */
      }

#ifdef FASTL_SSE
#endif

#ifdef FASTL_AVX
#endif

      
   protected:
      char* expand ( std::size_t _grow_size )
      {
	 char* p_new_space = static_cast<char*>(__Alloc :: allocate(_grow_size));

	 if( p_new_space != nullptr )
	 {
	    p_available = p_new_space;
	    p_end = p_available + _grow_size;
	 }
	 else // p_new_space == nullptr
	 {
	 }
	 
	 return p_available;
      }

   private:
      std::size_t  InitSize;
      std::size_t  GrowSize;
      
      char*        p_head;
      char*        p_available;
      char*        p_end;
      __Recycle    counter;
   };
   //
   // END OF NAMESPACE
}
