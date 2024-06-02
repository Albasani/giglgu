/*
 * $Id: LogAssert.h 238 2012-02-20 10:34:56Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_LOGGING_LOGASSERT_H
#define GIGLGU_LOGGING_LOGASSERT_H

#include <stdexcept>  // std::logic_error
#include <giglgu/logging/LogStream.h>

#define LOGFILE_QUOTE0(n) #n
#define LOGFILE_QUOTE1(n) LOGFILE_QUOTE0(n)
#define LOGFILE_FLF       __FILE__ ":" LOGFILE_QUOTE1(__LINE__) "\n"

#ifdef NDEBUG
# define LogAssert(c) ((void)0)
#else
# define LogAssert(c) \
  if (!(c)) { \
    static const char msg[] = "Assertion failed: " #c; \
    giglgu::logging::LogStream() << LOGFILE_FLF << msg << '\n'; \
    throw std::logic_error(msg); \
  }
#endif

#endif /* #ifndef GIGLGU_LOGGING_LOGASSERT_H */
