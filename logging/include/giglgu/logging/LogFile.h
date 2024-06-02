/*
 * $Id: LogFile.h 281 2012-06-02 10:05:30Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_LOGGING_LOGFILE_H
#define GIGLGU_LOGGING_LOGFILE_H

#include <giglgu/logging/Component.h>
#include <giglgu/logging/CriticalSection.h>

#include <iostream>	// std::ostream

namespace giglgu { namespace logging {

/**
 * @class LogFile
 * @note
 * None of the methods provided by this class are thread-safe.
 * Use getCS() to synchronize access to getStream().
 */
class GIGLGU_LOGGING_EXPORT LogFile
{
public:
  /** Initializes m_strm with std::cerr */
  LogFile();

  /** Calls close() */
  ~LogFile();

  /**
   * Deletes m_strm if it does not point to std::cerr,
   * then sets m_strm to std::cerr.
   */
  void close();

  /** Calls close(), then replaces m_strm with a new ofstream. */
  bool open(const char* filename);

  /**
   * @brief Creates a new instance if TheLogFile is 0.
   * @return *TheLogFile
   */
  static LogFile& GetInstance();

  /**
   * @brief Creates a new instance, assigns it to TheLogFile.
   * If TheLogFile is not 0 then the previous instance is deleted first.
   */
  static bool Setup(const char* filename);

  /**
   * @brief Retrieves value of envvar, calls Setup.
   */
  static bool SetupFromEnv(const char* envvar);

  /**
   * @brief Deletes TheLogFile and sets it to 0.
   */
  static void DeleteInstance();

  static void ReplaceFileNameMacros(std::string&);

  CriticalSection& getCS() { return m_cs; }
  std::ostream& getStream() { return *m_strm; }

private:
  static LogFile* TheLogFile;

private:
  CriticalSection m_cs;

  /**
   * @brief Pointer to an output stream.
   * @note
   * Directly using an instance of ofstream as member is problematic on
   * Windows. See warning C4251. Hence we use a pointer.
   */
  std::ostream* m_strm;
};

}} // namespace

#endif /* #ifndef GIGLGU_LOGGING_LOGFILE_H */
