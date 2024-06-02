/*
 * $Id: WinError.h 130 2012-02-09 23:06:39Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_WINDOWS_WINERROR_H
#define GIGLGU_WINDOWS_WINERROR_H

#if !defined(_WIN32)
# error This source is specific to WIN32.
#endif

#include <giglgu/windows/Component.h>

#include <iostream>
#include <string>

namespace giglgu { namespace windows {

/**
 * @class WinError
 * This is a light-weight wrapper around GetLastError and FormatMessage.
 * It deliberately has no virtual functions.
 * While the source is specific to the Windows API, we do not expose
 * the API in the header file (i.e., no <windows.h> in <WinError.h>).
 */
class GIGLGU_WINDOWS_EXPORT WinError
{
public:
  typedef unsigned ErrorType; // matches type DWORD

private:
  ErrorType m_error;

public:
  WinError(); // initialize m_error with GetLastError()
  WinError(ErrorType error);

  ErrorType getError() const { return m_error; }
  bool isError() const { return m_error != 0; }
  bool isEINTR() const { return false; }
  std::ostream& print(std::ostream& strm) const;
  std::string getString() const;
    
  static const char* GetErrorName(ErrorType error);

private:
  void* formatMessage() const;
};

inline std::ostream& operator<<(std::ostream& strm, const WinError& e)
{
  return e.print(strm);
}

}} // namespace

#endif /* #ifndef GIGLGU_WINDOWS_WINERROR_H*/
