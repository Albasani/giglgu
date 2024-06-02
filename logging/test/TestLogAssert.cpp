/*
 * $Id: TestLogAssert.cpp 238 2012-02-20 10:34:56Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/logging/LogAssert.h>
#include <giglgu/logging/LogFile.h>

#include <stdlib.h>     // EXIT_FAILURE

#define ENV_LOGFILE   "GIGLGU_LOGFILE"

// Do not import namespace "giglgu" at this point to test
// whether macro LogAssert works without.

int main(const int argc, const char** argv)
{
  if (!giglgu::logging::LogFile::SetupFromEnv(ENV_LOGFILE))
    return EXIT_FAILURE;
  {
    giglgu::logging::LogStream strm;
  #ifdef NDEBUG
    strm << "NDEBUG is defined.\n";
  #else
    strm << "NDEBUG is not defined.\n";
  #endif
  }
  try { LogAssert(true); LogAssert(false); }
  catch(const std::exception& exc)
  {
    giglgu::logging::LogStream strm;
    strm << "Caught std::exception, " << exc.what() << '\n';
  }
  catch(...)
  {
    giglgu::logging::LogStream strm;
    strm << "Caught unknown exception ...\n";
  }
  {
    giglgu::logging::LogStream strm;
    strm << LOGFILE_FLF;
  }
  giglgu::logging::LogFile::DeleteInstance();
  return 0;
}
