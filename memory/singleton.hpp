#include "common_header.h"
#include <list>

template< typename __ALLOC >
class pool
{
public:
   typedef __ALLOC                        allocator_type;
   typedef std::list< allocator_type >    allocator_manager_type;

private:
   static allocator_manager_type          m_Manager;
   //static allocator_type                  m_alloc;

protected:
   pool ( std::size_t _size )
   {
      manager.push_back( static_cast< allocator_type*>(nullptr) );
   }

   pool ( std::size_t _size )
   {
      allocator = __ALLOC( _size );
      manager.push_back( &allocator );
   }

   static void deallocate( void* _p )
   {
      allocator_manager_type::iterator iter;
      for( iter = m_Manager.begin(); iter != m_Manager.end(); ++iter )
      {
	 if( _p == iter->front() )
	 {
	    iter -> deallocate( _p );
	    m_Manager.erase( iter );
	    break;
	 }
      }
   }

   static void create_allocator ( std::size_t _size )
   {
      static allocator_manager_type manager;
      m_Manager = &( manager );
      m_Magager.emplace_front( _size );
   }


   static void get_instance ( std::size_t n )
   {
      if( instance == static_cast<allocator_type*>(nullptr) )
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


      



   // disable
   singleton() {}
   singleton( const allocator_type& clone ) {}
   singleton( allocator_type&& mv_cpy ) {}
   void operator= ( const allocator_type& clone ) {}
   ~singleton() {}
};

template< typename Alloc_t >
Alloc_t* singleton<Alloc_t> :: instance = nullptr;
