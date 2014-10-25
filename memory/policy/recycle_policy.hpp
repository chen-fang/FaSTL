#pragma once
#include <cstddef>  // provides: std::size_t

namespace fastl
{
   // BEGIN OF NAMESPACE
   //
   struct DoRecycle
   {
      DoRecycle() : counter(0) {}
      std::size_t counter;

      // Operators
      DoRecycle& operator++ ()
      { 
	 ++counter;
	 return *this;
      }

      DoRecycle operator++ (int)
      {
	 DoRecycle tmp = *this;
	 ++*this;
	 return tmp;
      }

      DoRecycle& operator-- ()
      { 
	 --counter;
	 return *this;
      }

      DoRecycle operator-- (int)
      {
	 DoRecycle tmp = *this;
	 --*this;
	 return tmp;
      }

      DoRecycle& operator+= (std::size_t a)
      {
	 (this->counter) += a;
	 return *this;
      }

      // functions
      inline std::size_t value() { return counter; }

      template< typename T >
      inline void reset ( T* p_head, T*& p_available )
      {
	 if( counter == 0 )
	 {
	    //std::cout << "reset" << std::endl;
	    p_available = p_head;
	 }
      }
   };


   struct NoRecycle
   {
      NoRecycle& operator++ ()                  { return *this; }
      NoRecycle operator++ (int)                { return *this; }
      NoRecycle& operator-- ()                  { return *this; }
      NoRecycle operator-- (int)                { return *this; }
      NoRecycle& operator+= (std::size_t)       { return *this; }
      inline std::size_t value() { return 1; }

      template< typename T >
      inline void reset( T* p_head, T*& p_available ) { }
   };
   //
   // END OF NAMESPACE
}
