#pragma once

struct OpAdd
{
   template< typename T >
   inline static T value ( T a, T b )
   {
      return ( a + b );
   }

   template< typename T1, typename T2 >
   inline static typename T1::size_type Get_Derivative ( const T1& t1, const T2& t2 )
   {
      return ( t1.derivative() + t2.derivative() );
   }
};

/*
struct OpSub
{
   template< typename T >
   inline static T apply ( const T& a, const T& b )
   {
      return a - b;
   }
};

struct OpMul
{
   template< typename T >
   static T apply ( const T& a, const T& b )
   {
      return a * b;
   }
};

struct OpDiv
{
   template< typename T >
   static T apply ( const T& a, const T& b )
   {
      return a / b;
   }
};
*/
