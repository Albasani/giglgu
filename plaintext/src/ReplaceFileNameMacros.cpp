/*
 * $Id: ReplaceFileNameMacros.cpp 254 2012-02-23 09:31:51Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/plaintext/ReplaceFileNameMacros.h>
#include <giglgu/plaintext/private.h>

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <windows.h> // GetCurrentProcessId
#endif

#include <string>	// std::string
#include <cstdlib>	// getenv
#include <ctime>	// time
#include <fstream>	// std::ofstream

using namespace giglgu::PlainText;

// "%02d:%02d:%02d" is more natural, but requires a POSIX file system.
static const char szTimeFormat[] = "%02d_%02d_%02d";

typedef char ProcessIDBuffer[32];
static int GetProcessID(ProcessIDBuffer buffer)
{
  return snprintf(buffer, sizeof(ProcessIDBuffer),
#ifdef _WIN32
    "%lu", GetCurrentProcessId()
#else
    "%ld", (long)getpid()
#endif
  );
}

void ReplaceFileNameMacros(std::string& s)
{
  const time_t now = time(0);
  size_t start = 0;
  for(;;)
  {
    size_t found = s.find('%', start);
    if (found == std::string::npos)
      return;
    if (found == s.length())
      return;
    const char c = s.at(found + 1);
    switch(c)
    {
      case 'P':
      {
        ProcessIDBuffer sz;
        const int len = GetProcessID(sz);
        s.replace(found, 2, sz);
        start = start + len - 2; 
        break;
      }
      case 'T':
      {
        struct tm* tm = localtime(&now);
        char sz[32];
        const int len = snprintf(sz, sizeof(sz), szTimeFormat,
          tm->tm_hour, tm->tm_min, tm->tm_sec);
        s.replace(found, 2, sz);
        start = start + len - 2; 
        break;
      }
      default:
        start += 2;
        break;
    }
  }
}
