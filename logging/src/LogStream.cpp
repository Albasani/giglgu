/*
 * $Id: LogStream.cpp 245 2012-02-21 09:34:56Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/logging/LogStream.h>
#include <giglgu/logging/LogFile.h>
#include <giglgu/logging/BadNullStream.h>

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#endif

#if defined(__linux__)
# include <sys/syscall.h>	// SYS_gettid
#endif

#include <ctime>	// time

using namespace giglgu::logging;

static BadNullStream nullStream;

LogStream::LogStream()
: m_lock( LogFile::GetInstance().getCS() )
, m_strm( LogFile::GetInstance().getStream() )
{
  m_strm << time(0)
#if defined(__linux__)
         << ' ' << syscall(SYS_gettid)
#endif
         << ' ';
}

LogStream::LogStream(bool enable)
: m_lock( LogFile::GetInstance().getCS() )
, m_strm( 
  enable
  ? LogFile::GetInstance().getStream()
  : nullStream
)
{
  m_strm << time(0)
#if defined(__linux__)
         << ' ' << syscall(SYS_gettid)
#endif
         << ' ';
}

LogStream::~LogStream()
{
  m_strm.flush();
}

