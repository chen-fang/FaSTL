#pragma once

/* allocate ( 0 )
 * 
 * If allocating 0 by user, allocate alignof(double) instead
 * to ensure alignment.
 *
 */

#define ALLOC_0 alignof(double)
