/*
 * $Id: Thread.cpp 271 2012-06-01 14:22:41Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/posix/Thread.h>
#include <giglgu/posix/ThreadAttr.h>
#include <giglgu/posix/private.h>

#include <iomanip>	// std::hex

using namespace giglgu::posix;

/*
 * The initializer of idOfMainThread is run before main(), i.e. in the
 * context of the main thread.
 * The POSIX API does not define a null value for pthread_t.
 * We use idOfMainThread instead to distinguish an initialized pthread_t
 * from a released one.
 */
static pthread_t idOfMainThread = pthread_self();

#define M_THREAD \
  reinterpret_cast<pthread_t&>(m_thread)
#define M_THREAD_CONST \
  reinterpret_cast<const pthread_t&>(m_thread)

Thread::Thread()
{
  M_THREAD = idOfMainThread;
}

Thread::Thread(PfnThread pfn, void* arg)
{
  const int e = pthread_create(&M_THREAD, 0, pfn, arg);
  PRINT_ERROR(e, pthread_create);
}

Thread::~Thread()
{
  if (M_THREAD != idOfMainThread)
    detach();
}

bool Thread::detach()
{
  const int e = pthread_detach(M_THREAD);
  PRINT_ERROR(e, pthread_detach);
  return e == 0;
}

bool Thread::join(void*& value)
{
  const int e = pthread_join(M_THREAD, &value);
  if (e != 0)
  {
    WriteErrno(e, "pthread_join failed.");
    return false;
  }
  M_THREAD = idOfMainThread;
  return true;
}

bool Thread::getCpuClockID(clockid_t& c) const
{
  const int e = pthread_getcpuclockid(M_THREAD_CONST, &c);
  PRINT_ERROR(e, pthread_getcpuclockid);
  return e == 0;
}

std::ostream& Thread::inspect(std::ostream& strm) const
{
  clockid_t c;
  if (getCpuClockID(c))
    strm << "getCpuClockID=0x" << std::hex << c << std::dec << '\n';

  return strm;
}

