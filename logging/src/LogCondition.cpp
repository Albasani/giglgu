/*
 * $Id: LogCondition.cpp 309 2012-06-19 15:05:49Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#include <giglgu/logging/LogCondition.inc>

#include <giglgu/logging/BadNullStream.h>
#include <giglgu/logging/ForwardingStream.h>
#include <giglgu/logging/ThreadLocalStorage.h>

#if defined(_WIN32)
# include <giglgu/windows/Atomic.h>
  using namespace giglgu::windows::atomic;
#else
# include <giglgu/posix/Atomic.h>
  using namespace giglgu::posix::atomic;
#endif

#include <cstring>      // strcmp

using namespace giglgu::logging;

#if defined(_WIN32)
static ThreadLocalStorage tlsForwardingStream;
#else
static void DeleteOstream(void* value)
{
  delete static_cast<std::ostream*>(value);
}
static ThreadLocalStorage tlsForwardingStream(DeleteOstream);
#endif

static TlsManaged< BadNullStream > tlsNullStream;
static SyncStreamSink sss(std::cerr);

LogCondition* LogCondition::m_first = 0;

LogCondition::LogCondition(const char* name, const BitName* bitNames)
: m_name(name)
, m_bitNames(bitNames)
, m_bits(0)
, m_next(0)
{
  m_next = FetchAndSwap(m_first, this);
}

LogCondition::~LogCondition()
{}

std::ostream& LogCondition::GetForwardingStream()
{
  std::ostream* result = static_cast<std::ostream*>(
    tlsForwardingStream.get()
  );
  if (result == 0)
  {
    result = new ForwardingStream(sss);
    tlsForwardingStream.set(result);
  }
  return *result;
}

std::ostream& LogCondition::GetBadNullStream()
{
  return tlsNullStream.create();
}

std::ostream& LogCondition::operator()(BitsT bit) const
{
  return isOneSet(bit) ? GetForwardingStream() : GetBadNullStream();
}

void LogCondition::OnThreadExit()
{
  tlsNullStream.destroy();
}

std::ostream& LogCondition::inspect(std::ostream& strm) const
{
  strm
  << m_name << "=0x"
  << std::hex << m_bits << std::dec
  ;
  if (m_bitNames != 0)
  {
    strm << "=";
    m_bitNames->decode(strm, m_bits, "|");
  }
  return strm << '\n';
}

bool LogCondition::NameIsLess::operator()(
  const LogCondition* a,
  const LogCondition* b
) const
{
  return strcmp(a->getName(), b->getName()) < 0;
}
