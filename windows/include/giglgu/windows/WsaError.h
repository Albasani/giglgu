/*
 * $Id: WsaError.h 165 2012-02-13 17:38:59Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_WINDOWS_WSAERROR_H
#define GIGLGU_WINDOWS_WSAERROR_H

#include <giglgu/windows/WinError.h>

namespace giglgu { namespace windows {

/**
 * @class WinError
 * This is a light-weight wrapper around WSAGetLastError and
 * FormatMessage. It deliberately has no virtual functions.
 * While the source is specific to the Windows API, we do not expose
 * the API in the header file (i.e., no <winsock2.h> in <WsaError.h>).
 */
class GIGLGU_WINDOWS_EXPORT WsaError : public WinError
{
public:
  typedef int ErrorType; // return type of WSAGetLastError
public:
  WsaError(); // initialize m_error with WSAGetLastError()
  WsaError(ErrorType error);
};

}} // namespace

#endif /* #ifndef GIGLGU_WINDOWS_WSAERROR_H */
