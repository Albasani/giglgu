/*
 * $Id: Thread.cpp 272 2012-06-01 14:58:39Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/windows/Thread.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// #include <iostream>  // std::cerr
// #include <string.h>  // strerror

using namespace giglgu::windows;

Thread::Thread(PfnThread pfn, void* parameter)
: m_handle(0)
, m_id(0)
{
  typedef int assert_HANDLE[
    sizeof(m_handle) == sizeof(::HANDLE) ? +1 : -1
  ];
  typedef int assert_DWORD[
    sizeof(m_id) == sizeof(::DWORD) ? +1 : -1
  ];

  m_handle = CreateThread(
    0, // lpThreadAttributes
    0, // dwStackSize
    pfn,
    parameter,
    0, // dwCreationFlags
    &m_id
  );  
}

Thread::~Thread()
{
  CloseHandle(m_handle);
}
