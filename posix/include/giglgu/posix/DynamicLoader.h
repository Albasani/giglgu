/*
 * $Id: DynamicLoader.h 285 2012-06-13 21:26:10Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_POSIX_DYNAMICLOADER_H
#define GIGLGU_POSIX_DYNAMICLOADER_H

#include <giglgu/posix/config.h>

#include <iostream>	// std::ostream

namespace giglgu { namespace posix {

class DynamicLoader
{
private:
  void* m_handle;

public:
  DynamicLoader(const char *filename = 0);
  ~DynamicLoader();

private:
  DynamicLoader(const DynamicLoader&); // no implementation
  DynamicLoader& operator=(const DynamicLoader&); // no implementation
};

}} // namespace

#endif
