#pragma once

#include "array.hpp"

namespace fastl
{
   namespace detail
   {
      template< typename vector_t >
      static vector_t vpv ( const vector_t v1, const vector_t& v2 )
      {
	 vector_t v = v1 + v2;
	 return v;
      }
   }
}
