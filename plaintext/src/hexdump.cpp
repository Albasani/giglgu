/*
 * $Id: hexdump.cpp 205 2012-02-16 16:25:43Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/plaintext/hexdump.h>

#include <cstdio>	// sprintf

namespace giglgu { namespace PlainText {

void hexdump(std::string& dst, const void* src, size_t srcLen, char separator)
{
  static const char szFormat[] = "%02X";
  const unsigned char* p = (const unsigned char*)src;
  if (srcLen-- > 0)
  {
    char sz[0x10];
    dst.append(sz, sprintf(sz, szFormat, (unsigned)*p++));	
    while(srcLen-- > 0)
    {
      dst.append(1, separator);
      dst.append(sz, sprintf(sz, szFormat, (unsigned)*p++));
    }
  }
}

}} // namespace
