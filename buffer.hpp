#pragma once

template< typename T, typename ALLOC >
class buffer
{
   typedef buffer<T,ALLOC> this_type;
public:
   buffer ()
      : size(_size), p_beg(nullptr), p_end(nullptr)
   {
      std::cout << "buffer :: ctor()" << std::endl;
   }

   buffer ( std::size_t _size )
      : size(_size), p_beg( ALLOC::allocate() ), p_end( p_begin+_size )
   {
      std::cout << "buffer :: ctor( size )" << std::endl;
   }

   buffer ( const this_type& _clone )
      : size( _clone.size() ), p_beg( ALLOC::allocate() ), p_end( p_beg+size )
   {
      fastl :: uninitialized_copy( p_beg, _clone.p_beg, _clone.p_end );

      std::cout << "buffer :: copy ctor" << std::endl;
   }

   buffer ( buffer&& _other )
      : size( _other.size() ), p_beg( _other.p_beg ), p_end( _other.p_end )
   {
      _other.p_beg = nullptr;
      _other.p_end = nullptr;

      std::cout << "buffer :: move ctor" << std::endl;
   }



   T& operator [] ( std::size_t i )
   {
      return *( p_beg + i );
   }

   buffer operator + ( const this_type& _other )
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

   buffer operator + ( this_type&& _other )
   {
      std::cout << "------------ + const && + ------------" << std::endl;

      this_type tmp( std::move(_other) );
      for( std::size_t i = 0; i < _other.size(); ++i )
      {
	 tmp[i] = (*this)[i] + _other[i];
      }
      return tmp;

      std::cout << "------------ + const && + ------------" << std::endl;
   }


private:
					   std::size_t size;
   T* p_beg;
   T* p_end;
}
