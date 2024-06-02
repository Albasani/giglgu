/*
 * $Id: Cond.cpp 265 2012-05-01 14:18:15Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/posix/Cond.h>
#include <giglgu/posix/CondAttr.h>
#include <giglgu/posix/Mutex.h>
#include <giglgu/posix/private.h>

#include <string.h>	// strerror

using namespace giglgu::posix;

#define M_COND		reinterpret_cast<pthread_cond_t&>(m_cond)
#define M_COND_CONST	reinterpret_cast<const pthread_cond_t&>(m_cond)

Cond::Cond()
{
  const int e = pthread_cond_init(&M_COND, 0);
  PRINT_ERROR(e, pthread_cond_init);
}

Cond::Cond(const CondAttr& attr)
{
  const pthread_condattr_t* p = static_cast<const pthread_condattr_t*>(attr.getAttr());
  const int e = pthread_cond_init(&M_COND, p);
  PRINT_ERROR(e, pthread_cond_init);
}

Cond::~Cond()
{
  const int e = pthread_cond_destroy(&M_COND);
  PRINT_ERROR(e, pthread_cond_destroy);
}

bool Cond::signal()
{
  const int e = pthread_cond_signal(&M_COND);
  PRINT_ERROR(e, pthread_cond_signal);
  return e == 0;
}

bool Cond::broadcast()
{
  const int e = pthread_cond_broadcast(&M_COND);
  PRINT_ERROR(e, pthread_cond_broadcast);
  return e == 0;
}

bool Cond::wait(Mutex& mutex)
{
  pthread_mutex_t* m = static_cast<pthread_mutex_t*>(mutex.getMutex());
  const int e = pthread_cond_wait(&M_COND, m);
  PRINT_ERROR(e, pthread_cond_wait);
  return e == 0;
}

int Cond::timedWait(Mutex& mutex, const timespec* abstime)
{
  pthread_mutex_t* m = static_cast<pthread_mutex_t*>(mutex.getMutex());
  const int e = pthread_cond_timedwait(&M_COND, m, abstime);
  PRINT_ERROR(e, pthread_cond_timedwait);
  return e;
}
