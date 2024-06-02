/*
 * $Id: Cond.h 265 2012-05-01 14:18:15Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_POSIX_CONDVAR_H
#define GIGLGU_POSIX_CONDVAR_H

#include <giglgu/posix/config.h>

struct timespec;

namespace giglgu { namespace posix {

class CondAttr;
class Mutex;

/**
 * @class Cond
 * @brief Wrapper for pthread_cond_t.
 * @note Class has no virtual methods by design.
 */
class Cond
{
private:
  // reserve space for pthread_cond_t
  long m_cond[
    (SIZEOF_pthread_cond_t + sizeof(long) - 1) / sizeof(long)
  ];

public:
  Cond();
  explicit Cond(const CondAttr&);
  ~Cond();

  bool signal();
  bool broadcast();
  bool wait(Mutex&);
  int timedWait(Mutex&, const timespec* abstime);

private:
  Cond(const Cond&); // no implementation
  Cond& operator=(const Cond&); // no implementation
};

}} // namespace

#endif
