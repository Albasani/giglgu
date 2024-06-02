/*
 * $Id: CriticalSection.h 145 2012-02-11 11:08:19Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_WINDOWS_CRITICALSECTION_H
#define GIGLGU_WINDOWS_CRITICALSECTION_H

#include <giglgu/windows/Component.h>

namespace giglgu { namespace windows {

/**
 * @class CriticalSection
 * @brief Wrapper for CRITICAL_SECTION
 */
class GIGLGU_WINDOWS_EXPORT CriticalSection
{
private:
  // reserve space for CRITICAL_SECTION
  long m_cs[
    (SIZEOF_CRITICAL_SECTION + sizeof(long) - 1) / sizeof(long)
  ];

public:
  /**
   * @class Lock
   * @brief Safe way to lock and unlock a CriticalSection.
   */
  class GIGLGU_WINDOWS_EXPORT Lock
  {
  private:
    CriticalSection& m_cs;
  public:
    Lock(CriticalSection& cs): m_cs(cs) { m_cs.enter(); }
    ~Lock() { m_cs.leave(); }

  private:
    Lock(); // no implementation
    Lock(const Lock&); // no implementation
    Lock& operator=(const Lock&); // no implementation
  };
  
public:
  CriticalSection();
  ~CriticalSection();
  void enter();
  void leave();

private:
  CriticalSection(const CriticalSection&); // no implementation
  CriticalSection& operator=(const CriticalSection&); // no implementation
};

}} // namespace

#endif
