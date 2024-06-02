/*
 * $Id: ForwardingSink.h 245 2012-02-21 09:34:56Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_LOGGING_FORWARDINGSINK
#define GIGLGU_LOGGING_FORWARDINGSINK

#include <giglgu/logging/Component.h>
#include <giglgu/logging/CriticalSection.h>

#include <iostream>	// std::ostream

namespace giglgu { namespace logging {

class GIGLGU_LOGGING_EXPORT ForwardingSink
{
public:
  ForwardingSink() {}
  virtual ~ForwardingSink();
  virtual bool write(const void* p, size_t len) = 0;
};

class GIGLGU_LOGGING_EXPORT SyncStreamSink : public ForwardingSink
{
private:
  CriticalSection m_cs;
  std::ostream& m_strm;

public:
  SyncStreamSink(std::ostream& m_strm);
  virtual ~SyncStreamSink();
  virtual bool write(const void* p, size_t len);
};

}} // namespace

#endif
