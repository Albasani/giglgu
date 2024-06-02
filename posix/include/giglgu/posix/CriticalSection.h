/*
 * $Id: CriticalSection.h 73 2012-02-06 00:04:12Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_POSIX_CRITICALSECTION_H
#define GIGLGU_POSIX_CRITICALSECTION_H

#include <giglgu/posix/Mutex.h>

namespace giglgu { namespace posix {

/**
 * @class CriticalSection
 * @brief A mutex that supports recursive locking.
 * @note Class has no virtual methods by design.
 */
class CriticalSection : public Mutex
{
public:
  CriticalSection();
  ~CriticalSection();

private:
  CriticalSection(const CriticalSection&); // no implementation
  CriticalSection& operator=(const CriticalSection&); // no implementation
};

}} // namespace

#endif
