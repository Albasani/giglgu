/*
 * $Id: TestWinError.cpp 276 2012-06-01 22:09:35Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/windows/WinError.h>
#include <giglgu/windows/WsaError.h>

#if !defined(_WIN32)
# error Code is specific to WIN32.
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>

#include <iostream>

using namespace giglgu::windows;

int main(const int argc, const char** argv)
{
  OSVERSIONINFO osvi;
  memset(&osvi, 0, 0);
  // A working call to GetVersionEx requires this:
  //   osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
  // By passing a value of 0 instead we are sure to receive an error.
  if (!GetVersionEx(&osvi))
  {
    WinError e;
    std::cerr << "GetVersionEx failed: " << e << '\n';
  }
  
  // Not calling WSAStartup is also an error.
  SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
  if (s == -1)
  {
    WsaError e;
    std::cerr << "socket failed: " << e << '\n';
  }
  
  return 0;
}
