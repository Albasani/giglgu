/*
 * $Id: LogStream.h 299 2012-06-17 16:21:31Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_LOGGING_LOGSTREAM_H
#define GIGLGU_LOGGING_LOGSTREAM_H

#include <giglgu/logging/Component.h>
#include <giglgu/logging/CriticalSection.h>

#include <iostream>	// std::ostream

namespace giglgu { namespace logging {

class LogCondition;

/**
 * @class LogStream
 */
class GIGLGU_LOGGING_EXPORT LogStream
{
public:
  /**
   * Initalize with stream and critical section returned by
   * LogFile::GetInstance().
   */
  LogStream();

  /**
   * Initalize m_lock with the critical section returned by
   * LogFile::GetInstance().getCS().
   * 
   * If enable is true then m_strm is initialized with the stream
   * returned by LogFile::GetInstance().getStream().
   *
   * If enable is false then m_strm is initialized with a instance of
   * BadNullStream.
   */
  LogStream(bool enable);

  /** Unlock the critical section */
  ~LogStream();

  template< typename T > 
  std::ostream& operator<<(const T& value) 
  { 
    return m_strm << value;
  } 

  bool operator!() const { return !m_strm; }
  bool fail() const { return m_strm.fail(); }
  operator bool() const { return !!m_strm; }    
  operator std::ostream&() const { return m_strm; }
  std::ostream& write(const char* s, std::streamsize n);

private:
  CriticalSection::Lock m_lock;
  std::ostream& m_strm;
};

inline std::ostream& LogStream::write(const char* s, std::streamsize n)
{
  return m_strm.write(s, n);
}

}} // namespace

#endif /* #ifndef GIGLGU_LOGGING_LOGSTREAM_H */
