/*
 * $Id: CondAttr.h 282 2012-06-02 10:06:06Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_POSIX_CONDATTR_H
#define GIGLGU_POSIX_CONDATTR_H

#include <giglgu/posix/config.h>

#include <iostream>

namespace giglgu { namespace posix {

/**
 * @class CondAttr
 * @brief Wrapper for pthread_condattr_t.
 * @note Class has no virtual methods by design.
 */
class CondAttr
{
private:
  // Reserve storage for a pthread_condattr_t
  long m_attr[
    (SIZEOF_pthread_condattr_t + sizeof(long) - 1) / sizeof(long)
  ];

public:
  typedef int clockid_t;

  enum ClockID
  {
    REALTIME,
    MONOTONIC,
    PROCESS_CPUTIME_ID,
    THREAD_CPUTIME_ID
  };

public:
  CondAttr();
  ~CondAttr();

  bool setPShared(int pshared);
  CondAttr& setPShared(bool);
  bool getPShared() const;

  bool setClock(clockid_t clock_id);
  CondAttr& setClock(ClockID id);
  bool getClock(clockid_t& clock_id) const;

  std::ostream& inspect(std::ostream& strm) const;

  // Returns -1 on error.
  static CondAttr::clockid_t GetClockID(CondAttr::ClockID);

  static const char* GetClockName(clockid_t id);
  static const char* GetClockName(CondAttr::ClockID);

  void* getAttr() { return &m_attr; }
  const void* getAttr() const { return &m_attr; }

private:
  CondAttr(const CondAttr&); // no implementation
  CondAttr& operator=(const CondAttr&); // no implementation
};

inline const char* CondAttr::GetClockName(CondAttr::ClockID id)
{
  return GetClockName(GetClockID(id));
}

}} // namespace

#endif
