/*
 * $Id: TestCriticalSection.cpp 134 2012-02-10 13:09:29Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/windows/CriticalSection.h>

#include <iostream>	// std::cout
#include <cstdlib>	// EXIT_SUCCESS

using namespace giglgu::windows;

int main(const int argc, const char** argv)
{
  CriticalSection cs;
  cs.enter();
    cs.enter();
      std::cout << "Succesfully locked CriticalSection twice.\n";
    cs.leave();
  cs.leave();

  return EXIT_SUCCESS;
}
