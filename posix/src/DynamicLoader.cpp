/*
 * $Id: DynamicLoader.cpp 291 2012-06-15 23:38:19Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/posix/DynamicLoader.h>
#include <giglgu/posix/DynamicLoaderError.h>
#include <giglgu/posix/private.h>

#include <dlfcn.h>	// dlclose
#include <stdio.h>

using namespace giglgu::posix;

DynamicLoader::DynamicLoader(const char* filename)
: m_handle(0)
{
  if (filename == 0)
    return;
  m_handle = dlopen(filename, RTLD_LAZY);
  if (m_handle != 0)
    return;
  DynamicLoaderError dle;
  WriteErrno(
    0, "%s\ndlopen(%s) failed.\n",
    dle.getString().c_str(), filename
  );
}

DynamicLoader::~DynamicLoader()
{
  if (m_handle == 0)
    return;
  if (0 == dlclose(m_handle))
    return;
  DynamicLoaderError dle;
  WriteErrno(
    0, "%s\ndlclose failed.\n",
    dle.getString().c_str()
  );
}
