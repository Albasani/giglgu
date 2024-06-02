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
#ifndef GIGLGU_WINDOWS_ATOMIC_H
#define GIGLGU_WINDOWS_ATOMIC_H

#include <giglgu/windows/Component.h>

#if defined(_MSC_VER)
# include <intrin.h>
#endif

namespace giglgu { namespace windows { namespace atomic {

template< typename Type >
Type* FetchAndSwap(Type*& dst, Type* new_value)
{
#if defined(_MSC_VER) && defined(_M_AMD64)
  return _InterlockedExchangePointer(&dst, new_value);
#elif defined(_MSC_VER) && defined(_M_IX86)
  typedef int assert_size[sizeof(dst) == sizeof(long) ? +1 : -1];
  return reinterpret_cast<Type*>(
    _InterlockedExchange(
      reinterpret_cast<long*>(&dst),
	  reinterpret_cast<long>(new_value)
	)
  );
#else
# error No implementation for FetchAndSwap.
#endif
}

}}} // namespace

#endif /* #ifndef GIGLGU_WINDOWS_WSAERROR_H */
