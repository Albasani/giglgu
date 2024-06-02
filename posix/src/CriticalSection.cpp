/*
 * $Id: CriticalSection.cpp 73 2012-02-06 00:04:12Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/posix/CriticalSection.h>
#include <giglgu/posix/MutexAttr.h>

using namespace giglgu::posix;

CriticalSection::CriticalSection()
: Mutex( MutexAttr().setType(MutexAttr::MutexRecursive) )
{}

CriticalSection::~CriticalSection()
{}
