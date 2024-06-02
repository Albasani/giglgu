/*
 * $Id: TestLogCondition.cpp 309 2012-06-19 15:05:49Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/logging/LogCondition.inc>
#include <giglgu/logging/LogConditionMap.h>
#include <giglgu/logging/LogFile.h>
#include <giglgu/logging/LogStream.h>
#include <giglgu/logging/ForwardingStream.h>

#include <iomanip>	// std::setw
#include <stdlib.h>     // EXIT_FAILURE
#include <sstream>
#include <cassert>

#define ENV_LOGFILE   "GIGLGU_LOGFILE"

using namespace giglgu::logging;

static const LogCondition::BitName lcBits[] =
{
  { 1, "a" },
  { 2, "b" },
  { 0 }
};
LogCondition lc("huhu", lcBits);
LogCondition lc1("one");
LogCondition lcDuplicate("one");
LogCondition lc2("two");

static void run()
{
  if (lc(1))
  {
    LogStream()
    << "getname=" << lc.getName()
    << "\ngetbits=0x" << std::hex << lc.getBits() << std::dec
    << "\nlc(1)=" << lc(1)
    << '\n';
  }
  {
    LogStream(lc.isOneSet(1)) << __LINE__ << '\n';
  }
  {
    LogStream ls(lc.isOneSet(1));
    if (!!ls)
      ls << __LINE__ << '\n';
    if (!ls.fail())
      ls << __LINE__ << '\n';
    if (ls)
      ls << __LINE__ << '\n';
      
    std::ostream& strm = ls;
    if (!!strm)
      strm << __LINE__ << '\n';
    if (!strm.fail())
      strm << __LINE__ << '\n';
    if (strm)
      strm << __LINE__ << '\n';
  }  
}

static void print(const LogCondition& lc)
{
  std::cout << lc.getName() << "\n";
}

int main(const int argc, const char** argv)
{
  if (!LogFile::SetupFromEnv(ENV_LOGFILE))
    return EXIT_FAILURE;

  std::cout << "=== Testing SyncStreamSink and ForwardingStream ===\n";
	
  SyncStreamSink sss(std::cout);
  ForwardingStream fs(sss);

  std::cout << "fs.fail=" << fs.fail() << "\n";
  std::cout << "fs.bad=" << fs.bad() << "\n";

  fs << "huhu\n";
  fs.flush();
  fs << "anton\n";
  fs << std::endl;

  std::cout << "=== Testing LogCondition ===\n";  
  LogCondition::ForEachV(print);
  run();
  lc.setBits(1, 1);
  lc.setBits(3, 2);
  run();

  std::cout << "\n=== Testing LogConditionMap ===\n";  
  LogConditionMap lcm;
  lcm.inspect(std::cout);

  LogFile::DeleteInstance();
  return 0;
}
