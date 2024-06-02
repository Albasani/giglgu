/*
 * $Id: ThreadLocalStorage.cpp 251 2012-02-21 14:51:06Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/windows/ThreadLocalStorage.h>
#include <giglgu/windows/WinError.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace giglgu::windows;

ThreadLocalStorage::ThreadLocalStorage()
: m_key(TlsAlloc())
{
  typedef int assert_DWORD[sizeof(ThreadLocalStorage::DWORD) == sizeof(::DWORD) ? +1 : -1];
  typedef int assert_InvalidKey[InvalidKey == TLS_OUT_OF_INDEXES ? +1 : -1];  
  if (m_key == TLS_OUT_OF_INDEXES)
  {
    WinError e;
    std::cerr << "TlsAlloc failed: " << e << '\n';
  }
}

ThreadLocalStorage::~ThreadLocalStorage()
{
  if (!TlsFree(m_key))
  {
    WinError e;
    std::cerr << "TlsFree(" << m_key << ") failed: " << e << '\n';
  }
}

void* ThreadLocalStorage::get() const
{
  return TlsGetValue(m_key);
}

void ThreadLocalStorage::set(void* value) const
{
  if (!TlsSetValue(m_key, value))
  {
    WinError e;
    std::cerr << "TlsSetValue(" << m_key << ") failed: " << e << '\n';
  }
}
