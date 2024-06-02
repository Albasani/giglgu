/*
 * $Id: DynamicLoaderError.cpp 291 2012-06-15 23:38:19Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/posix/DynamicLoaderError.h>

#include <dlfcn.h>	// dlerror

using namespace giglgu::posix;

DynamicLoaderError::DynamicLoaderError()
{
  const char* p = dlerror();
  if (p != 0)
    m_msg = p;
}

DynamicLoaderError::~DynamicLoaderError()
{}

void DynamicLoaderError::printString(std::ostream& strm) const
{
  strm << m_msg;
}
