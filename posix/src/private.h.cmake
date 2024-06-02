/*
 * $Id: private.h.cmake 284 2012-06-13 21:22:02Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_PTHREAD_PRIVATE_H
#define GIGLGU_PTHREAD_PRIVATE_H

#include <giglgu/posix/config.h>
#include <giglgu/posix/Component.h>

#include <stdarg.h>	// va_list

#cmakedefine HAVE_pthread_mutexattr_getrobust_np	@HAVE_pthread_mutexattr_getrobust_np@
#cmakedefine HAVE_pthread_mutexattr_setrobust_np	@HAVE_pthread_mutexattr_setrobust_np@
#cmakedefine HAVE_pthread_mutexattr_getrobust		@HAVE_pthread_mutexattr_getrobust@
#cmakedefine HAVE_pthread_mutexattr_setrobust		@HAVE_pthread_mutexattr_setrobust@
#cmakedefine HAVE_pthread_getattr_np			@HAVE_pthread_getattr_np@
#cmakedefine HAVE_inet_ntop				@HAVE_inet_ntop@

namespace giglgu { namespace posix {

  typedef void (*PfnWriteErrnoV)(int error, va_list va, const char* format);
  extern PfnWriteErrnoV WriteErrnoV;

  /* calls WriteErrnoV */
  void WriteErrno(int error, const char* format, ...);

}} // namespace

#define PRINT_ERROR(e, function) \
  if (e != 0) { \
    WriteErrno(e, #function " failed."); \
  }

#endif
