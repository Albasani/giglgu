/*
 * $Id: TestDynamicLoader.cpp 291 2012-06-15 23:38:19Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/windows/DynamicLoader.h>

#include <cstdlib>	// EXIT_SUCCESS

using namespace giglgu::windows;

int main(const int argc, const char** argv)
{
  { DynamicLoader dl; }
  { DynamicLoader dl("huhu"); }
  return EXIT_SUCCESS;
}
