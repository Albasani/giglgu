/*
 * $Id: CriticalSection.cpp 77 2012-02-06 01:44:32Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/windows/CriticalSection.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// #include <iostream>	// std::cerr
// #include <string.h>	// strerror

using namespace giglgu::windows;

#define M_CS	reinterpret_cast<CRITICAL_SECTION&>(m_cs)

CriticalSection::CriticalSection()
{
  InitializeCriticalSection(&M_CS);
}

CriticalSection::~CriticalSection()
{
  DeleteCriticalSection(&M_CS);
}

void CriticalSection::enter()
{
  EnterCriticalSection(&M_CS);
}

void CriticalSection::leave()
{
  LeaveCriticalSection(&M_CS);
}