/*
 * $Id: ThreadLocalStorage.h 251 2012-02-21 14:51:06Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_WINDOWS_THREADLOCALSTORAGE_H
#define GIGLGU_WINDOWS_THREADLOCALSTORAGE_H

#include <giglgu/windows/Component.h>

namespace giglgu { namespace windows {

/**
 * @class Thread
 * @brief Wrapper for TlsAlloc/.
 * @note Class has no virtual methods by design.
 */
class GIGLGU_WINDOWS_EXPORT ThreadLocalStorage
{
public:
  typedef unsigned long DWORD;
  enum { InvalidKey = -1 };
  
private:
  DWORD m_key;

public:
  ThreadLocalStorage();
  ~ThreadLocalStorage();

  bool isValid() const { return m_key != InvalidKey; }
  void* get() const;
  void set(void* value) const;

private:
  ThreadLocalStorage(const ThreadLocalStorage&); // no implementation
  ThreadLocalStorage& operator=(const ThreadLocalStorage&); // no implementation
};

}} // namespace

#endif
