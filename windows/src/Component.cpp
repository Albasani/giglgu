/*
 * $Id: Component.cpp 251 2012-02-21 14:51:06Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/windows/private.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// using namespace giglgu::windows;

#if defined(giglgu_windows_EXPORTS)
BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID)
{
  switch(fdwReason)
  {
    case DLL_PROCESS_ATTACH:
      // TlsAlloc ?
      break;
    case DLL_THREAD_ATTACH:
      // TlsSetValue ?
      break;
    case DLL_THREAD_DETACH:
      // TlsGetValue ?
      break;
    case DLL_PROCESS_DETACH:
      // TlsGetValue, TlsFree ?
      break;
    default:
      break; 
  } 
  return TRUE;
}
#endif