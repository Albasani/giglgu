/*
 * $Id: CondAttr.cpp 282 2012-06-02 10:06:06Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#if !defined(_POSIX_C_SOURCE)
  // To pull in CLOCK_* definitions through <sys/time.h>
# define _POSIX_C_SOURCE	199309L
#endif

#include <giglgu/posix/CondAttr.h>
#include <giglgu/posix/private.h>

#include <string.h>	// strerror
#include <sys/time.h>

using namespace giglgu::posix;

typedef int assert_clockid[
  sizeof(CondAttr::clockid_t) == sizeof(::clockid_t) ? +1 : -1
];

#define M_ATTR		reinterpret_cast<pthread_condattr_t&>(m_attr)
#define M_ATTR_CONST	reinterpret_cast<const pthread_condattr_t&>(m_attr)

CondAttr::CondAttr()
{
  const int e = pthread_condattr_init(&M_ATTR);
  PRINT_ERROR(e, pthread_condattr_init);
}

CondAttr::~CondAttr()
{
  const int e = pthread_condattr_destroy(&M_ATTR);
  PRINT_ERROR(e, pthread_condattr_destroy);
}

bool CondAttr::setPShared(int pshared)
{
  const int e = pthread_condattr_setpshared(&M_ATTR, pshared);
  PRINT_ERROR(e, pthread_condattr_setpshared);
  return e == 0;
}

CondAttr& CondAttr::setPShared(bool isShared)
{
  setPShared(isShared ? PTHREAD_PROCESS_SHARED : PTHREAD_PROCESS_PRIVATE);
  return *this;
}

bool CondAttr::getPShared() const
{
  int s;
  const int e = pthread_condattr_getpshared(&M_ATTR_CONST, &s);
  PRINT_ERROR(e, pthread_condattr_getpshared);
  return e == 0 && s == PTHREAD_PROCESS_SHARED;
}

bool CondAttr::setClock(clockid_t clock_id)
{
  /*
   * 2012-06-02, libc6-2.11.1-0ubuntu7.10, x64
   * Calling pthread_condattr_setclock with CLOCK_PROCESS_CPUTIME_ID
   * causes a segmentation fault.
   */
#ifdef CLOCK_PROCESS_CPUTIME_ID
  if (clock_id == CLOCK_PROCESS_CPUTIME_ID)
    return false;
#endif
#ifdef CLOCK_THREAD_CPUTIME_ID
  if (clock_id == CLOCK_THREAD_CPUTIME_ID)
    return false;
#endif
  const int e = pthread_condattr_setclock(&M_ATTR, clock_id);
  PRINT_ERROR(e, pthread_condattr_setclock);
  return e == 0;
}

CondAttr& CondAttr::setClock(ClockID id)
{
  const clockid_t c = GetClockID(id);
  if (c != -1)
    setClock(c);
  return *this;
}

CondAttr::clockid_t CondAttr::GetClockID(CondAttr::ClockID id)
{
  switch(id)
  {
#ifdef CLOCK_REALTIME
    case REALTIME: return CLOCK_REALTIME;
#endif
#ifdef CLOCK_MONOTONIC
    case MONOTONIC: return CLOCK_MONOTONIC;
#endif
#ifdef CLOCK_PROCESS_CPUTIME_ID
    case PROCESS_CPUTIME_ID: return CLOCK_PROCESS_CPUTIME_ID;
#endif
#ifdef CLOCK_THREAD_CPUTIME_ID
    case THREAD_CPUTIME_ID: return CLOCK_THREAD_CPUTIME_ID;
#endif
    default: return -1;
  }
}

bool CondAttr::getClock(clockid_t& clock_id) const
{
  const int e = pthread_condattr_getclock(&M_ATTR_CONST, &clock_id);
  PRINT_ERROR(e, pthread_condattr_setclock);
  return e == 0;
}

const char* CondAttr::GetClockName(clockid_t id)
{
  switch(id)
  {
#ifdef CLOCK_REALTIME
    case CLOCK_REALTIME: return "CLOCK_REALTIME";
#endif
#ifdef CLOCK_MONOTONIC
    case CLOCK_MONOTONIC: return "CLOCK_MONOTONIC";
#endif
#ifdef CLOCK_PROCESS_CPUTIME_ID
    case CLOCK_PROCESS_CPUTIME_ID: return "CLOCK_PROCESS_CPUTIME_ID";
#endif
#ifdef CLOCK_THREAD_CPUTIME_ID
    case CLOCK_THREAD_CPUTIME_ID: return "CLOCK_THREAD_CPUTIME_ID";
#endif
    default: return 0;
  }
}

std::ostream& CondAttr::inspect(std::ostream& strm) const
{
  strm << "pshared=" << getPShared() << '\n';
  clockid_t c;
  if (getClock(c))
  {
    const char* name = GetClockName(c);
    if (name == 0)
      strm << "clock=" << c << '\n';
    else
      strm << "clock=" << name << '\n';
  }
  return strm;
}
