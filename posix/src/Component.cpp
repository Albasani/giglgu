/*
 * $Id: Component.cpp 286 2012-06-14 18:29:22Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/posix/private.h>

#include <cstdio>	// snprintf
#include <cstring>	// strerror
// #include <sys/uio.h>	// writev
#include <unistd.h>	// STDERR_FILENO


namespace giglgu { namespace posix {

void WriteErrno(int code, const char* format, ...)
{
  va_list va;
  va_start(va, format);
  WriteErrnoV(code, va, format);
  va_end(va);
}

static void WriteErrnoVStderr(int code, va_list va, const char* format)
{
  char sz[0x1000];
  int len = 0;

  if (code != 0)
  {
    const char* errmsg = strerror(code);
    len = snprintf(sz, sizeof(sz), "Error %d: %s. ", code, errmsg);
    if (len < 0 || (size_t)len >= sizeof(sz))
      len = strlen(sz);
  }

  if ((size_t)len < sizeof(sz))
  {
    const size_t remaining = sizeof(sz) - len;
    const int rc = vsnprintf(sz + len, remaining, format, va);
    if (rc < 0 || (size_t)rc >= remaining)
      len = strlen(sz);
    else
      len += rc;
  }

  write(STDERR_FILENO, sz, len);
}

/* variable with external linkage */
PfnWriteErrnoV WriteErrnoV = WriteErrnoVStderr;

}} // namespace
