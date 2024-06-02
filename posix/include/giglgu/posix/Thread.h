/*
 * $Id: Thread.h 114 2012-02-07 15:36:55Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_POSIX_THREAD_H
#define GIGLGU_POSIX_THREAD_H

#include <giglgu/posix/config.h>

#include <iostream>	// std::ostream

namespace giglgu { namespace posix {

class ThreadAttr;

/**
 * @class Thread
 * @brief Wrapper for pthread_t.
 * @note Class has no virtual methods by design.
 */
class Thread
{
private:
  // reserve space for pthread_t
  long m_thread[
    (SIZEOF_pthread_t + sizeof(long) - 1) / sizeof(long)
  ];

public:
  typedef int clockid_t;
  typedef void* (*PfnThread)(void*);

public:
  /**
   *  Retrieves the ID of the main thread. Offers very limited functionality
   * Can be used to query information. See ThreadAttr(const Thread&).
   */
  Thread();

  Thread(PfnThread, void*);

  /** Calls detach unless join has been called before. */
  ~Thread();

  bool detach();
  bool join(void*& value);

  /* Cast this to (pthread_t*) if you really need it. */
  const void* getInternal() const { return &m_thread; }

  bool getCpuClockID(clockid_t&) const;
  std::ostream& inspect(std::ostream&) const;

private:
  Thread(const Thread&); // no implementation
  Thread& operator=(const Thread&); // no implementation
};

}} // namespace

#endif
