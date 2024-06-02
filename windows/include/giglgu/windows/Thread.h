/*
 * $Id: Thread.h 147 2012-02-11 11:24:21Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_WINDOWS_THREAD_H
#define GIGLGU_WINDOWS_THREAD_H

#include <giglgu/windows/Component.h>

namespace giglgu { namespace windows {

/**
 * @class Thread
 * @brief Wrapper for CreateThread.
 */
class GIGLGU_WINDOWS_EXPORT Thread
{
public:
  typedef void* HANDLE;
  typedef unsigned long DWORD;
  typedef DWORD(__stdcall *PfnThread)(void* parameter);

private:
  HANDLE m_handle;
  DWORD m_id;

public: 
  Thread(PfnThread pfn, void* parameter);
  ~Thread();

private:
  Thread(const Thread&); // no implementation
  Thread& operator=(const Thread&); // no implementation
};

}} // namespace

#endif
