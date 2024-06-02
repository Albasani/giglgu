/*
 * $Id: ThreadAttr.cpp 271 2012-06-01 14:22:41Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/posix/ThreadAttr.h>
#include <giglgu/posix/Thread.h>
#include <giglgu/posix/private.h>

#include <iomanip>	// std::hex

using namespace giglgu::posix;

#define M_ATTR \
  reinterpret_cast<pthread_attr_t&>(m_attr)
#define M_ATTR_CONST \
  reinterpret_cast<const pthread_attr_t&>(m_attr)

#define CALL_0(func) \
  const int e = func(&M_ATTR); \
  if (e != 0) \
  { \
    WriteErrno(e, #func " failed."); \
    return; \
  }

#define CALL_1(attr, func, param, returnOnError) \
  const int e = func(&attr, param); \
  if (e != 0) \
  { \
    WriteErrno(e, #func " failed."); \
    return returnOnError; \
  }

ThreadAttr::ThreadAttr()
{
  CALL_0(pthread_attr_init);
}

ThreadAttr::ThreadAttr(const Thread& thread)
{
#if HAVE_pthread_getattr_np
  {
    const int e = pthread_getattr_np(
      *static_cast<const pthread_t*>(thread.getInternal()),
      &M_ATTR
    );
    if (e == 0)
      return;
    WriteErrno(e, "pthread_getattr_np failed.");
  }
#endif
  CALL_0(pthread_attr_init);
}

ThreadAttr::~ThreadAttr()
{
  CALL_0(pthread_attr_destroy);
}

bool ThreadAttr::setStackSize(size_t stacksize)
{
  CALL_1(M_ATTR, pthread_attr_setstacksize, stacksize, false);
  return true;
}

bool ThreadAttr::getStackSize(size_t& stacksize) const
{
  CALL_1(M_ATTR_CONST, pthread_attr_getstacksize, &stacksize, false);
  return true;
}

bool ThreadAttr::setDetachState(int detachState)
{
  CALL_1(M_ATTR, pthread_attr_setdetachstate, detachState, false);
  return true;
}

bool ThreadAttr::getDetachState(int& detachState) const
{
  CALL_1(M_ATTR_CONST, pthread_attr_getdetachstate, &detachState, false);
  return true;
}

bool ThreadAttr::Has(Feature f)
{
  switch(f)
  {
#if HAVE_pthread_getattr_np
    case FeaGetAttrNP: return true;
#endif
    default: return false;
  }
}

std::ostream& ThreadAttr::inspect(std::ostream& strm) const
{
  size_t stacksize;
  if (getStackSize(stacksize))
    strm << "stacksize=0x" << std::hex << stacksize << std::dec << '\n';

  int detachState;
  if (getDetachState(detachState))
  {
    strm << "detachState=";
    switch(detachState)
    { 
      case PTHREAD_CREATE_DETACHED: strm << "PTHREAD_CREATE_DETACHED"; break;
      case PTHREAD_CREATE_JOINABLE: strm << "PTHREAD_CREATE_JOINABLE"; break;
      default: strm << detachState; break;
    }
    strm << '\n';
  }
  return strm;
}
