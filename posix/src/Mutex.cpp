/*
 * $Id: Mutex.cpp 103 2012-02-07 09:09:30Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/posix/Mutex.h>
#include <giglgu/posix/MutexAttr.h>
#include <giglgu/posix/private.h>

using namespace giglgu::posix;

#define M_MUTEX reinterpret_cast<pthread_mutex_t&>(m_mutex)

Mutex::Mutex()
{
  const int e = pthread_mutex_init(&M_MUTEX, 0);
  PRINT_ERROR(e, pthread_mutex_init);
}

Mutex::Mutex(const MutexAttr& attr)
{
  const int e = pthread_mutex_init(
    &M_MUTEX,
    static_cast<const pthread_mutexattr_t*>(attr.getAttr())
  );
  PRINT_ERROR(e, pthread_mutex_init);
}

Mutex::~Mutex()
{
  const int e = pthread_mutex_destroy(&M_MUTEX);
  PRINT_ERROR(e, pthread_mutex_destroy);
}

bool Mutex::lock()
{
  const int e = pthread_mutex_lock(&M_MUTEX);
  PRINT_ERROR(e, pthread_mutex_lock);
  return e == 0;
}

bool Mutex::unlock()
{
  const int e = pthread_mutex_unlock(&M_MUTEX);
  PRINT_ERROR(e, pthread_mutex_unlock);
  return e == 0;
}
