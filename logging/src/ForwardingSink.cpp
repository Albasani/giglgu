/*
 * $Id: ForwardingSink.cpp 244 2012-02-20 21:49:19Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/logging/ForwardingSink.h>

using namespace giglgu::logging;

ForwardingSink::~ForwardingSink()
{}

SyncStreamSink::SyncStreamSink(std::ostream& strm)
: m_strm(strm)
{}

SyncStreamSink::~SyncStreamSink()
{}

bool SyncStreamSink::write(const void* p, size_t len)
{
  CriticalSection::Lock lock(m_cs);
  m_strm.write(static_cast<const char*>(p), len);
  return true;
}
