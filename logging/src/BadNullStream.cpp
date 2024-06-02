/*
 * $Id: BadNullStream.cpp 231 2012-02-19 20:43:37Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/logging/BadNullStream.h>

using namespace giglgu::logging;

BadNullStream::BadNullStream()
: std::ios(0)
, std::ostream(0)
{}
  
BadNullStream::~BadNullStream()
{}