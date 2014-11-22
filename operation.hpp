#pragma once

// vector1 + vector2
template< typename vector_type >
vector_type vpv ( vector_type v1, const vector_type& v2 )
{
   return ( v1 + v2 );
}
// vector1 - vector2
template< typename vector_type >
vector_type vmv ( vector_type v1, const vector_type& v2 )
{
   return ( v1 - v2 );
}
// scalar * vector
template< typename scalar_type, typename vector_type >
vector_type stv ( scalar_type s, const vector_type& v )
{
   vector_type tmp( v.size() );
   for( std::size_t i = 0; i < v.size(); ++i )
   {
      tmp[i] = s * v[i];
   }
   return tmp;
}
// vector / scalar
template< typename scalar_type, typename vector_type >
vector_type vds ( const vector_type& v, scalar_type s )
{
   vector_type tmp( v.size() );
   for( std::size_t i = 0; i < v.size(); ++i )
   {
      tmp[i] = v[i] / s;
   }
   return tmp;
}
// scalar * vector + scalar * vector
template< typename scalar_type, typename vector_type >
vector_type stvpstv ( scalar_type s1, const vector_type& v1,
		      scalar_type s2, const vector_type& v2 )
{
   vector_type tmp( v1.size() );
   for( std::size_t i = 0; i < tmp.size(); ++i )
   {
      tmp[i] = s1 * v1[i] + s2 * v2[i];
   }
   return tmp;
}
// scalar * vector - scalar * vector
template< typename scalar_type, typename vector_type >
vector_type stvmstv ( scalar_type s1, const vector_type& v1,
		      scalar_type s2, const vector_type& v2 )
{
   vector_type tmp( v1.size() );
   for( std::size_t i = 0; i < tmp.size(); ++i )
   {
      tmp[i] = s1 * v1[i] - s2 * v2[i];
   }
   return tmp;
}
// ( scalar * vector - scalar * vector ) / scalar
template< typename scalar_type, typename vector_type >
vector_type stvmstv_ds ( scalar_type s1, const vector_type& v1,
			 scalar_type s2, const vector_type& v2,
			 scalar_type s3 )
{
   vector_type tmp( v1.size() );
   for( std::size_t i = 0; i < tmp.size(); ++i )
   {
      tmp[i] = ( s1 * v1[i] - s2 * v2[i] ) / s3;
   }
   return tmp;
}
