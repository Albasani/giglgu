/*
 * $Id: Atomic.h 306 2012-06-18 15:34:46Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_POSIX_ATOMIC_H
#define GIGLGU_POSIX_ATOMIC_H

#include <giglgu/posix/config.h>

namespace giglgu { namespace posix { namespace atomic {

template< typename Type >
Type* FetchAndSwap(Type*& dst, Type* new_value)
{
#if defined(__GNUC__)
  return __sync_lock_test_and_set(&dst, new_value);
#else
# error No implementation for FetchAndSwap.
#endif
}

}}} // namespace

#endif
