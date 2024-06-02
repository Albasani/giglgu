/*
 * $Id: TestForwarding.cpp 281 2012-06-02 10:05:30Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/logging/ForwardingStream.h>

using namespace giglgu::logging;

int main(const int argc, const char** argv)
{
  SyncStreamSink sss(std::cerr);
  ForwardingStream fs(sss);

  std::cerr << "fs.fail=" << fs.fail() << "\n";
  std::cerr << "fs.bad=" << fs.bad() << "\n";

  fs << "huhu\n";
  fs.flush();
  fs << "anton\n";
  fs << std::endl;

  return 0;
}
