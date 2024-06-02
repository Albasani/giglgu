/*
 * $Id: LogCondition.inc 297 2012-06-16 21:06:10Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_LOGGING_LOGCONDITION_INC
#define GIGLGU_LOGGING_LOGCONDITION_INC

#include <giglgu/logging/LogCondition.h>

#if defined(_MSC_VER)
# include <intrin.h>
#endif

namespace giglgu { namespace logging {

/********************************************************************/
#if defined(_MSC_VER)
/********************************************************************/

inline void LogCondition::setBits(BitsT andMask, BitsT orMask)
{
  // { m_bits = (m_bits & andMask) | orMask; }
  _InterlockedAnd(&m_bits, andMask);
  _InterlockedOr(&m_bits, orMask);
}

inline bool LogCondition::isOneSet(BitsT bit) const
{
  // { return (m_bits & bit) != 0; }
  return 0 != (_InterlockedOr(const_cast<BitsT*>(&m_bits), 0) & bit);
}

inline LogCondition::BitsT LogCondition::getBits() const
{
  return _InterlockedOr(const_cast<BitsT*>(&m_bits), 0);
}

/********************************************************************/
#elif defined(__GNUC__)
/********************************************************************/

inline void LogCondition::setBits(BitsT andMask, BitsT orMask)
{
  // { m_bits = (m_bits & andMask) | orMask; }
  __sync_and_and_fetch(&m_bits, andMask);
  __sync_or_and_fetch(&m_bits, orMask);
}

inline bool LogCondition::isOneSet(BitsT bit) const
{
  // { return (m_bits & bit) != 0; }
  return 0 != (__sync_fetch_and_or(const_cast<BitsT*>(&m_bits), 0) & bit);
}

inline LogCondition::BitsT LogCondition::getBits() const
{
  return __sync_fetch_and_or(const_cast<BitsT*>(&m_bits), 0);
}

/********************************************************************/
#endif
/********************************************************************/

template<class Function>
Function LogCondition::ForEachV(Function f)
{
  for(const LogCondition* p = m_first; p != 0; p = p->m_next)
    f(*p);
  return f;
}

template<class Functor>
Functor& LogCondition::ForEachR(Functor& f)
{
  for(const LogCondition* p = m_first; p != 0; p = p->m_next)
    f(*p);
  return f;
}

}} // namespace

#endif /* #ifndef GIGLGU_LOGGING_LOGCONDITION_H */
