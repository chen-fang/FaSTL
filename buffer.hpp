#pragma once

#include "initialization/initialization.h"

template< typename T, typename ALLOC >
class buffer
{
   typedef buffer<T,ALLOC> this_type;
public:
   buffer ()
      : sz(0), p_beg(nullptr), p_end(nullptr)
   {
      std::cout << "buffer :: ctor()" << std::endl;
   }

   buffer ( std::size_t _size )
      : sz(_size), p_beg( static_cast<T*>(ALLOC::allocate()) ), p_end( p_beg+_size )
   {
      fastl :: construct_array( p_beg, p_end );

      std::cout << "buffer :: ctor( size )" << std::endl;
   }

   buffer ( const this_type& _clone )
      : sz( _clone.sz ), p_beg( static_cast<T*>(ALLOC::allocate()) ), p_end( p_beg+sz )
   {
      fastl :: uninitialized_copy( p_beg, _clone.p_beg, _clone.p_end );

      std::cout << "buffer :: copy ctor" << std::endl;
   }

   buffer ( buffer&& _other )
      : sz( _other.sz ), p_beg( _other.p_beg ), p_end( _other.p_end )
   {
      _other.p_beg = nullptr;
      _other.p_end = nullptr;

      std::cout << "buffer :: move ctor" << std::endl;
   }

   ~buffer ()
   {
      std::cout << "buffer :: dtor" << std::endl;

      sz = 0;
      ALLOC :: deallocate( static_cast<void*>(p_beg) );
      p_end = nullptr;
   }

   std::size_t size() const
   {
      return sz;
   }

   void resize( std::size_t n )
   {
      sz = n;
      p_beg = ALLOC :: allocate();
      p_end = p_beg + sz;
   }

   T* begin()
   {
      return p_beg;
   }

   T* begin() const
   {
      return p_beg;
   }

   T* end()
   {
      return p_end;
   }

   T& operator [] ( std::size_t i )
   {
      return *( p_beg + i );
   }

   T& operator [] ( std::size_t i ) const
   {
      return *( p_beg + i );
   }

   this_type operator + ( const this_type& _other )
   {
      std::cout << "------------ + const & + -------------" << std::endl;

      this_type tmp( _other.size() );
      for( std::size_t i = 0; i < _other.size(); ++i )
      {
	 tmp[i] = (*this)[i] + _other[i];
      }
      return tmp;

      std::cout << "------------ + const & + -------------" << std::endl;
   }

   this_type operator + ( this_type&& _other )
   {
      std::cout << "------------ + const && + ------------" << std::endl;

      this_type tmp( std::move(_other) );

      for( std::size_t i = 0; i < _other.size(); ++i )
      {
	 tmp[i] += (*this)[i];
      }
      return tmp;

      std::cout << "------------ + const && + ------------" << std::endl;
   }


   this_type& operator = ( const this_type& _clone )
   {
      std::cout << "assignment" << std::endl;

      if( sz == 0 )
	 this.resize( _clone.size() );

      this_type tmp( _clone.size() );
      for( std::size_t i = 0; i < _clone.size(); ++i )
      {
	 tmp[i] = (*this)[i] + _clone[i];
      }
      return tmp;
   }

   this_type& operator = ( this_type&& _other )
   {
      std::cout << "move assignment" << std::endl;

      sz = _other.size();
      p_beg = _other.begin();
      p_end = _other.end();
      //
      _other.p_beg = nullptr;
      _other.p_end = nullptr;
   }


private:
   std::size_t sz;
   T* p_beg;
   T* p_end;
};
