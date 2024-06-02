/*
 * $Id: ThreadLocalStorage.cpp 243 2012-02-20 15:34:56Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/posix/ThreadLocalStorage.h>
// #include <giglgu/posix/ErrnoError.h>
#include <giglgu/posix/private.h>

#include <iomanip>	// std::hex

using namespace giglgu::posix;

#define M_KEY \
  reinterpret_cast<pthread_key_t&>(m_key)
#define M_KEY_CONST \
  reinterpret_cast<const pthread_key_t&>(m_key)

ThreadLocalStorage::ThreadLocalStorage(PfnDestructor pfn)
{
  const int e = pthread_key_create(&M_KEY, pfn);
  PRINT_ERROR(e, "pthread_key_create");
}

ThreadLocalStorage::~ThreadLocalStorage()
{
  const int e = pthread_key_delete(M_KEY);
  PRINT_ERROR(e, "pthread_key_delete");
}

void* ThreadLocalStorage::get() const
{
  return pthread_getspecific(M_KEY_CONST);
}

void ThreadLocalStorage::set(const void* value) const
{
  const int e = pthread_setspecific(M_KEY_CONST, value);
  PRINT_ERROR(e, "pthread_setspecific");
}
