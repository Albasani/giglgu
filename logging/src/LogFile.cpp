/*
 * $Id: LogFile.cpp 281 2012-06-02 10:05:30Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/logging/LogFile.h>

#include <giglgu/plaintext/private.h>

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <windows.h> // GetCurrentProcessId
#endif

#include <string>	// std::string
#include <cstdlib>	// getenv
#include <ctime>	// time
#include <fstream>	// std::ofstream

using namespace giglgu::logging;

// "%02d:%02d:%02d" is more natural, but requires a POSIX file system.
static const char szTimeFormat[] = "%02d_%02d_%02d";

LogFile* LogFile::TheLogFile = 0;

// static BadNullStream nullStream;

LogFile::LogFile()
: m_strm(&std::cerr)
{}

LogFile::~LogFile()
{
  close();
}

void LogFile::close()
{
  if (m_strm != &std::cerr)
    delete m_strm;
  m_strm = &std::cerr;
}

bool LogFile::open(const char* pszFilename)
{
  close();

  std::string filename(pszFilename);
  ReplaceFileNameMacros(filename);
  std::ofstream* strm = new std::ofstream(filename.c_str());
  if (strm->is_open())
  {
    m_strm = strm;
    return true;
  }
  delete strm;
  std::cerr << "Warning: Can't open log file " << filename << "\n";
  return false;  
}

typedef char ProcessIDBuffer[32];
static int GetProcessID(ProcessIDBuffer buffer)
{
  return snprintf(buffer, sizeof(ProcessIDBuffer),
#ifdef _WIN32
    "%lu", GetCurrentProcessId()
#else
    "%ld", (long)getpid()
#endif
  );
}

void LogFile::ReplaceFileNameMacros(std::string& s)
{
  const time_t now = time(0);
  size_t start = 0;
  for(;;)
  {
    size_t found = s.find('%', start);
    if (found == std::string::npos)
      return;
    if (found == s.length())
      return;
    const char c = s.at(found + 1);
    switch(c)
    {
      case 'P':
      {
        ProcessIDBuffer sz;
        const int len = GetProcessID(sz);
        s.replace(found, 2, sz);
        start = start + len - 2; 
        break;
      }
      case 'T':
      {
        struct tm* tm = localtime(&now);
        char sz[32];
        const int len = snprintf(sz, sizeof(sz), szTimeFormat,
          tm->tm_hour, tm->tm_min, tm->tm_sec);
        s.replace(found, 2, sz);
        start = start + len - 2; 
        break;
      }
      default:
        start += 2;
        break;
    }
  }
}

bool LogFile::SetupFromEnv(const char* envvar)
{
  if (envvar == 0)
  {
    std::cerr << "Parameter envvar is 0.\n";
    return false;
  }
  const char* const pszFilename = getenv(envvar);
  if (pszFilename == 0)
  {
    std::cerr << "Environment variable " << envvar << " is not defined.\n";
    return false;
  }
  return Setup(pszFilename);
}

LogFile& LogFile::GetInstance()
{
  if (TheLogFile == 0)
    TheLogFile = new LogFile;
  return *TheLogFile;
}

bool LogFile::Setup(const char* pszFilename)
{
  return LogFile::GetInstance().open(pszFilename);
}

void LogFile::DeleteInstance()
{
  delete TheLogFile; TheLogFile = 0;
}
