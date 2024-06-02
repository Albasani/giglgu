/*
 * $Id: MutexAttr.h 114 2012-02-07 15:36:55Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_POSIX_MUTEXATTR_H
#define GIGLGU_POSIX_MUTEXATTR_H

#include <giglgu/posix/config.h>

namespace giglgu { namespace posix {

/**
 * @class MutexAttr
 * @brief Wrapper for pthread_mutexattr_t.
 * @note Class has no virtual methods by design.
 */
class MutexAttr
{
private:
  // Reserve storage for a pthread_mutexattr_t
  long m_attr[
    (SIZEOF_pthread_mutexattr_t + sizeof(long) - 1) / sizeof(long)
  ];

public:
  enum Robust { MutexStalled, MutexRobust };
  enum Type { MutexDefault, MutexNormal, MutexErrorCheck, MutexRecursive };
  enum Feature { FeaSetRobust, FeaGetRobust };

public:
  MutexAttr();
  ~MutexAttr();

  const void* getAttr() const { return m_attr; }

  bool setType(int type);
  bool getType(int& type);
  MutexAttr& setType(Type t);

  bool setRobust(int type);
  bool getRobust(int& type);
  MutexAttr& setRobust(Robust r);

  static bool Has(Feature);

private:
  MutexAttr(const MutexAttr&); // no implementation
  MutexAttr& operator=(const MutexAttr&); // no implementation
};

}} // namespace

#endif
