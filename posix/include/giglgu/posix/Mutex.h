/*
 * $Id: Mutex.h 265 2012-05-01 14:18:15Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_POSIX_MUTEX_H
#define GIGLGU_POSIX_MUTEX_H

#include <giglgu/posix/config.h>

namespace giglgu { namespace posix {

class MutexAttr;

/**
 * @class Mutex
 * @brief Wrapper for pthread_mutex_t.
 * @note Class has no virtual methods by design.
 */
class Mutex
{
private:
  // reserve space for pthread_mutex_t
  long m_mutex[
    (SIZEOF_pthread_mutex_t + sizeof(long) - 1) / sizeof(long)
  ];

public:
  /**
   * @class Lock
   * @brief Safe way to lock and unlock a Mutex.
   */
  class Lock
  {
  private:
    Mutex& m_mutex;
  public:
    Lock(Mutex& mutex): m_mutex(mutex) { mutex.lock(); }
    ~Lock() { m_mutex.unlock(); }

  private:
    Lock(); // no implementation
    Lock(const Lock&); // no implementation
    Lock& operator=(const Lock&); // no implementation
  };

public:
  Mutex();
  explicit Mutex(const MutexAttr&);
  ~Mutex();
  bool lock();
  bool unlock();

  void* getMutex() { return &m_mutex; }

private:
  Mutex(const Mutex&); // no implementation
  Mutex& operator=(const Mutex&); // no implementation
};

}} // namespace

#endif
