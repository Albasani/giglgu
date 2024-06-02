/*
 * $Id: TestThreadAttr.cpp 98 2012-02-06 22:35:15Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/posix/ThreadAttr.h>
#include <giglgu/posix/Thread.h>

#include <iostream>	// std::cout
#include <iomanip>	// std::hex

using namespace giglgu::posix;

int main(const int argc, const char** argv)
{
  Thread mainThread;
  mainThread.inspect(std::cout);

  ThreadAttr a(mainThread);
  std::cout << "FeaGetAttrNP=" << ThreadAttr::Has(ThreadAttr::FeaGetAttrNP) << '\n';
  a.inspect(std::cout);

  return 0;
}
