/*
 * $Id: ThreadLocalStorage.h 243 2012-02-20 15:34:56Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_POSIX_THREADLOCALSTORAGE_H
#define GIGLGU_POSIX_THREADLOCALSTORAGE_H

#include <giglgu/posix/config.h>

#include <iostream>	// std::ostream

namespace giglgu { namespace posix {

/**
 * @class Thread
 * @brief Wrapper for pthread_t.
 * @note Class has no virtual methods by design.
 */
class ThreadLocalStorage
{
private:
  // reserve space for pthread_key_t
  long m_key[
    (SIZEOF_pthread_key_t + sizeof(long) - 1) / sizeof(long)
  ];

public:
  typedef void (*PfnDestructor)(void*);

public:
  ThreadLocalStorage(PfnDestructor pfn = 0);
  ~ThreadLocalStorage();

  void* get() const;
  void set(const void* value) const;

private:
  ThreadLocalStorage(const ThreadLocalStorage&); // no implementation
  ThreadLocalStorage& operator=(const ThreadLocalStorage&); // no implementation
};

}} // namespace

#endif
