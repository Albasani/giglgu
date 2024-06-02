/*
 * $Id: WsaError.cpp 96 2012-02-06 21:28:31Z alba $
 *
 * Copyright 2011-2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/windows/WsaError.h>

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>

using namespace giglgu::windows;

WsaError::WsaError()
: WinError(WSAGetLastError())
{}

WsaError::WsaError(ErrorType error)
: WinError(error)
{}
