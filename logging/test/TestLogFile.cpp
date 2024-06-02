/*
 * $Id: TestLogFile.cpp 238 2012-02-20 10:34:56Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/logging/LogFile.h>
#include <giglgu/logging/LogStream.h>

#include <iomanip>	// std::setw
#include <stdlib.h>     // EXIT_FAILURE

#if !defined(_WIN32)
# include <signal.h>    // SIGALRM
#endif

#define ENV_LOGFILE   "GIGLGU_LOGFILE"

using namespace giglgu::logging;

#if !defined(_WIN32)
void on_SIGALRM(int)
{
  exit(1); // abort with error code
}
#endif

static void printArgv(const int argc, const char** argv)
{
  LogStream strm;
  for(int i = 0; i < argc; ++i)
  {
    strm
    << std::setw(2) << i
    << ' '
    << argv[i]
    << '\n';
  }
}

int main(const int argc, const char** argv)
{
  if (!LogFile::SetupFromEnv(ENV_LOGFILE))
    return EXIT_FAILURE;
#if !defined(_WIN32)
  signal(SIGALRM, on_SIGALRM);
  alarm(10); // set up a timeout
#endif
  {
    LogStream strm;
    strm << "Huhu\n";
    printArgv(argc, argv); // do a nested lock
  }  
#if !defined(_WIN32)
  alarm(0); // cancel timeout
#endif
  LogFile::DeleteInstance();
  return 0;
}
