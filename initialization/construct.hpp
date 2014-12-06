#pragma once

/* Purposes:
 *
 * 1) Call constructors
 * 2) Set value
 * 3) Copy to uninitialized buffer
 * 4) Call destructors
 *
 */

namespace fastl
{
   template< typename T >
   struct CTR // ConsTRuct
   {
      static inline void set_zero  ( T* _p );
      static inline void set_zero  ( T* _p_beg, T* _p_end );
      static inline void set_value ( T* _p, T value );
      static inline void set_value ( T* _p_beg, T* _p_end, T value );

      static inline void construct        ( T* _p );
      static inline void construct_buffer ( T* _p_beg, T* _p_end );

      template< typename T1, typename... Args >
      static inline void construct ( T* _p, T1&& _arg1, Args&&... _args );

      template< typename T1, typename... Args >
      static inline void construct_buffer ( T* _p_beg, T* _p_end, T1&& _arg1, Args&&... _args );

      static inline void destroy        ( T* _p );
      static inline void destroy_buffer ( T* _p_beg, T* _p_end );

      static inline void uninitialized_copy    ( T* _p_dest, T* _src_beg, T* _src_end );
      static inline void uninitialized_copy_mv ( T* _p_dest, T* _src_beg, T* _src_end );
   };
}

#include "construct.ipp"
