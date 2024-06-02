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
#include <giglgu/windows/DynamicLoader.h>
#include <giglgu/windows/private.h>

#include <stdio.h>

using namespace giglgu::windows;

DynamicLoader::DynamicLoader(const char* filename)
: m_module(0)
{
  if (filename == 0)
    return;  
}

DynamicLoader::~DynamicLoader()
{
  if (m_module == 0)
    return;
}
