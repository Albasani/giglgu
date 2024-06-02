/*
 * $Id: ThreadAttr.h 114 2012-02-07 15:36:55Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_POSIX_THREADATTR_H
#define GIGLGU_POSIX_THREADATTR_H

#include <giglgu/posix/config.h>

#include <cstddef>	// size_t
#include <iostream>	// std::iostream

namespace giglgu { namespace posix {

class Thread;

/**
 * @class ThreadAttr
 * @brief Wrapper for pthread_attr_t.
 * @note Class has no virtual methods by design.
 */
class ThreadAttr
{
private:
  // reserve space for pthread_attr_t
  long m_attr[
    (SIZEOF_pthread_attr_t + sizeof(long) - 1) / sizeof(long)
  ];

public:
  enum Feature { FeaGetAttrNP };

public:
  ThreadAttr();
  ~ThreadAttr();

  /* Requires pthread_getattr_np.
   * Falls back to pthread_attr_init on error. */
  explicit ThreadAttr(const Thread&);

  bool setStackSize(size_t stacksize);
  bool getStackSize(size_t& stacksize) const;

  bool setDetachState(int detachstate);
  bool getDetachState(int& detachstate) const;

  std::ostream& inspect(std::ostream&) const;
  static bool Has(Feature);

private:
  ThreadAttr(const ThreadAttr&); // no implementation
  ThreadAttr& operator=(const ThreadAttr&); // no implementation
};

}} // namespace

#endif
