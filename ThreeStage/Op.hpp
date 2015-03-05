#pragma once

struct OpAdd
{
   template< typename T >
   inline static T apply ( const T& a, const T& b )
   {
      return a + b;
   }
};

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
