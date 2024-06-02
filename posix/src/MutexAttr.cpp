/*
 * $Id: MutexAttr.cpp 102 2012-02-07 09:04:03Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/posix/MutexAttr.h>
#include <giglgu/posix/private.h>

#include <string.h>	// strerror

using namespace giglgu::posix;

#define M_ATTR		reinterpret_cast<pthread_mutexattr_t&>(m_attr)

MutexAttr::MutexAttr()
{
  const int e = pthread_mutexattr_init(&M_ATTR);
  PRINT_ERROR(e, pthread_mutexattr_init);
}

MutexAttr::~MutexAttr()
{
  const int e = pthread_mutexattr_destroy(&M_ATTR);
  PRINT_ERROR(e, pthread_mutexattr_destroy);
}

bool MutexAttr::setType(int type)
{
  const int e = pthread_mutexattr_settype(&M_ATTR, type);
  PRINT_ERROR(e, pthread_mutexattr_settype);
  return e == 0;
}

bool MutexAttr::getType(int& type)
{
  const int e = pthread_mutexattr_gettype(&M_ATTR, &type);
  PRINT_ERROR(e, pthread_mutexattr_gettype);
  return e == 0;
}

bool MutexAttr::setRobust(int robust)
{
#if HAVE_pthread_mutexattr_setrobust
  const int e = pthread_mutexattr_setrobust(&M_ATTR, robust);
  PRINT_ERROR(e, pthread_mutexattr_setrobust);
  return e == 0;
#elif HAVE_pthread_mutexattr_setrobust_np
  const int e = pthread_mutexattr_setrobust_np(&M_ATTR, robust);
  PRINT_ERROR(e, pthread_mutexattr_setrobust_np);
  return e == 0;
#else
  return false;
#endif
}

bool MutexAttr::getRobust(int& robust)
{
#if HAVE_pthread_mutexattr_getrobust
  const int e = pthread_mutexattr_getrobust(&M_ATTR, &robust);
  PRINT_ERROR(e, pthread_mutexattr_getrobust);
  return e == 0;
#elif HAVE_pthread_mutexattr_getrobust_np
  const int e = pthread_mutexattr_getrobust_np(&M_ATTR, &robust);
  PRINT_ERROR(e, pthread_mutexattr_getrobust_np);
  return e == 0;
#else
  return false;
#endif
}

MutexAttr& MutexAttr::setType(Type t)
{
  int i;
  switch(t)
  {
    case MutexNormal:     i = PTHREAD_MUTEX_NORMAL;     break;
    case MutexErrorCheck: i = PTHREAD_MUTEX_ERRORCHECK; break;
    case MutexRecursive:  i = PTHREAD_MUTEX_RECURSIVE;  break;
    case MutexDefault:    i = PTHREAD_MUTEX_RECURSIVE;  break;
    default: return *this;
  }
  setType(i);
  return *this;
}

MutexAttr& MutexAttr::setRobust(Robust r)
{
  setRobust(r == MutexRobust ? PTHREAD_MUTEX_ROBUST : PTHREAD_MUTEX_STALLED);
  return *this;
}

bool MutexAttr::Has(Feature f)
{
  switch(f)
  {
#if HAVE_pthread_mutexattr_getrobust || HAVE_pthread_mutexattr_getrobust_np
    case FeaGetRobust: return true;
#endif
#if HAVE_pthread_mutexattr_setrobust || HAVE_pthread_mutexattr_setrobust_np
    case FeaSetRobust: return true;
#endif
    default: return false;
  }
}
