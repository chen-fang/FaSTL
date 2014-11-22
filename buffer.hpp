
#pragma once

#include "initialization/initialization.h"

template< typename T, typename ALLOC >
class buffer
{
public:
   typedef buffer<T,ALLOC> this_type;
  
public:
   buffer ()
      : p_beg(nullptr), p_end(nullptr)
   {
      std::cout << "buffer :: ctor()" << std::endl;
   }

   buffer ( std::size_t _size )
      : p_beg( static_cast<T*>(ALLOC::allocate()) ),
	p_end( p_beg + _size )
   {
      fastl :: construct_buffer( p_beg, p_end );

      std::cout << "buffer :: ctor( size )" << std::endl;
   }

   buffer ( const this_type& _clone )
      : p_beg( static_cast<T*>(ALLOC::allocate()) ),
	p_end( p_beg + _clone.size() )
   {
      fastl :: uninitialized_copy( p_beg, _clone.p_beg, _clone.p_end );

      std::cout << "buffer :: copy ctor" << std::endl;
   }

   buffer ( buffer&& _other )
      : p_beg( _other.p_beg ),
	p_end( _other.p_end )
   {
      _other.p_beg = nullptr;
      _other.p_end = nullptr;

      std::cout << "buffer :: move ctor" << std::endl;
   }

   ~buffer ()
   {
      std::cout << "buffer :: dtor" << std::endl;

      ALLOC :: deallocate( static_cast<void*>(p_beg) );
      p_end = nullptr;
   }

   std::size_t size() const
   {
      return ( p_end - p_beg );
   }

   void resize( std::size_t _size )
   {
      if( p_beg == nullptr )
      {
	 p_beg = static_cast<T*>( ALLOC :: allocate() );
	 p_end = p_beg + _size;
      }
      else
      {
	 p_end = p_beg + _size;
      }
   }

   T* front ()        { return p_beg; }
   T* front () const  { return p_beg; }
   T* back  ()        { return p_end; };
   T* back  () const  { return p_end; }


   T& operator [] ( std::size_t i )
   {
      return *( p_beg + i );
   }

   T& operator [] ( std::size_t i ) const
   {
      return *( p_beg + i );
   }




   this_type& operator = ( const this_type& _clone );
   this_type& operator = ( this_type&& _other );

   //this_type operator + ( this_type&& _other );   
   this_type operator + ( const this_type& _other );
   this_type operator - ( const this_type& _other );

   this_type& operator += ( const this_type& _other );
   this_type& operator -= ( const this_type& _other );

   
private:
   T* p_beg;
   T* p_end;
};




template< typename T, typename ALLOC >
buffer<T,ALLOC>& buffer<T,ALLOC> :: operator = ( const this_type& _clone )
{
   //std::cout << "assignment" << std::endl;

   if( this != &_clone )
   {
      this->resize( _clone.size() );
      for( std::size_t i = 0; i < _clone.size(); ++i )
      {
	 (*this)[i] = _clone[i];
      }
   }
   return *this;
}

template< typename T, typename ALLOC >
buffer<T,ALLOC>& buffer<T,ALLOC> :: operator = ( this_type&& _other )
{
   //std::cout << "move assignment" << std::endl;
   T* tmp_beg = p_beg;
   T* tmp_end = p_end;
   
   p_beg = _other.p_beg;
   p_end = _other.p_end;
   //
   _other.p_beg = tmp_beg;
   _other.p_end = tmp_end;

   return *this;
}

template< typename T, typename ALLOC >
buffer<T,ALLOC> buffer<T,ALLOC> :: operator + ( const this_type& _other )
{
   //std::cout << "------------ + const & + -------------" << std::endl;

   this_type tmp( _other.size() );
   for( std::size_t i = 0; i < _other.size(); ++i )
   {
      tmp[i] = (*this)[i] + _other[i];
   }
   return tmp;

   //std::cout << "------------ + const & + -------------" << std::endl;
}
// template< typename T, typename ALLOC >
// this_type buffer<T,ALLOC> :: operator + ( this_type&& _other )
// {
//    //std::cout << "------------ + const && + ------------" << std::endl;

//    this_type tmp( std::move(_other) );

//    for( std::size_t i = 0; i < _other.size(); ++i )
//    {
//       tmp[i] += (*this)[i];
//    }
//    return tmp;

//    //std::cout << "------------ + const && + ------------" << std::endl;
// }

template< typename T, typename ALLOC >
buffer<T,ALLOC> buffer<T,ALLOC> :: operator += ( const this_type& _other )
{
   this_type tmp( _other.size() );
   for( std::size_t i = 0; i < _other.size(); ++i )
   {
      (*this)[i] += _other[i];
   }
   return tmp;
}

template< typename T, typename ALLOC >
buffer<T,ALLOC>& buffer<T,ALLOC> :: operator -= ( const this_type& _other )
{
   for( std::size_t i = 0; i < _other.size(); ++i )
   {
      (*this)[i] -= _other[i];
   }
   return tmp;
}
