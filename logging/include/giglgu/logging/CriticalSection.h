/*
 * $Id: CriticalSection.h 224 2012-02-18 21:08:21Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_LOGGING_CRITICALSECTION_H
#define GIGLGU_LOGGING_CRITICALSECTION_H

#if defined(_WIN32)
# include <giglgu/windows/CriticalSection.h>
#else
# include <giglgu/posix/CriticalSection.h>
#endif

namespace giglgu { namespace logging {

#if defined(_WIN32)
  typedef giglgu::windows::CriticalSection CriticalSection;
#else
  typedef giglgu::posix::CriticalSection CriticalSection;
#endif

}} // namespace

#endif
