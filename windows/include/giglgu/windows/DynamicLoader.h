/*
 * $Id: DynamicLoader.h 291 2012-06-15 23:38:19Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_WINDOWS_DYNAMICLOADER_H
#define GIGLGU_WINDOWS_DYNAMICLOADER_H

#include <giglgu/windows/config.h>

#include <iostream>	// std::ostream

namespace giglgu { namespace windows {

class DynamicLoader
{
typedef 
  void* HMODULE;

private:
  HMODULE m_module;

public:
  DynamicLoader(const char *filename = 0);
  ~DynamicLoader();

private:
  DynamicLoader(const DynamicLoader&); // no implementation
  DynamicLoader& operator=(const DynamicLoader&); // no implementation
};

}} // namespace

#endif
