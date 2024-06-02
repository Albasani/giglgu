/*
 * $Id: ThreadLocalStorage.h 256 2012-02-23 13:02:55Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_LOGGING_THREADLOCALSTORAGE_H
#define GIGLGU_LOGGING_THREADLOCALSTORAGE_H

#if defined(_WIN32)
# include <giglgu/windows/ThreadLocalStorage.h>
#else
# include <giglgu/posix/ThreadLocalStorage.h>
#endif

namespace giglgu { namespace logging {

#if defined(_WIN32)
  typedef giglgu::windows::ThreadLocalStorage ThreadLocalStorage;
#else
  typedef giglgu::posix::ThreadLocalStorage ThreadLocalStorage;
#endif

template< class ManagedClass >
class TlsManaged : public ThreadLocalStorage
{
public:
  static void Destroy(ManagedClass* mc)
  {
    delete mc;
  }
  void destroy()
  {
    delete static_cast<ManagedClass*>(get());
    set(0);
  }
  ManagedClass& create()
  {
    ManagedClass* result = static_cast<ManagedClass*>(get());
    if (result == 0)
    {
      result = new ManagedClass;
      set(result);
    }
    return *result;
  }
};

}} // namespace

#endif
