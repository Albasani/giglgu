/*
 * $Id: LogCondition.h 308 2012-06-19 00:30:34Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_LOGGING_LOGCONDITION_H
#define GIGLGU_LOGGING_LOGCONDITION_H

#include <giglgu/logging/Component.h>
#include <giglgu/plaintext/BitName.h>

#include <iostream>	// std::ostream

#if defined(_MSC_VER)
# include <intrin.h>
#endif

namespace giglgu { namespace logging {

/**
 * @class LogCondition
 *
 * @note
 * Instances of LogCondition are created in outer-most scope
 * and thus have static lifetime. In a typical program the
 * constructor is executed before main, in a single threaded
 * environment. 
 * The destructor is called after main. Whether other threads
 * are still active at this time is implementation-dependent.
 * 
 * @note
 * The constructor maintains a static, single-linked list of
 * all instances. Atomic operations are used to add items to
 * the list. This allows to load shared libraries containing
 * instances of LogCondition at run-time. However, there is
 * no support for unloading libraries. The destructor does
 * not unlink items from the single-linked list.
 * 
 * @note
 * The implementation of setBits, operator(), getBits(), and
 * for_each is contained in file "LogCondition.inc".
 */
class GIGLGU_LOGGING_EXPORT LogCondition
{
public:
  struct NameIsLess
  {
    bool operator()(const LogCondition*, const LogCondition*) const;
  };

public:
#if defined(_MSC_VER)
  typedef long BitsT;
#else
  typedef unsigned BitsT;
#endif

  typedef giglgu::PlainText::BitName<
    BitsT, std::ostream, const char*
  > BitName;

private:
  const char* m_name;
  const BitName* m_bitNames;
  BitsT m_bits;
  const LogCondition* m_next;  

private:
  static LogCondition* m_first;  

public:
  LogCondition(
    const char* name,
    const BitName* bitNames = 0
  );

  /* Does nothing */
  ~LogCondition();
   
  BitsT getBits() const;
  void setBits(BitsT andMask, BitsT orMask);
  bool isOneSet(BitsT) const;

  const char* getName() const { return m_name; }
  const BitName* getBitNames() const { return m_bitNames; }

  /**
   * @return
   * - An instance of BadNullStream if bit is not set.
   * - An instance of ForwardingStream if bit is set.
   */
  std::ostream& operator()(BitsT bit) const;

  static std::ostream& GetForwardingStream();
  static std::ostream& GetBadNullStream();
  static void OnThreadExit();

  template< class Function >
  static Function ForEachV(Function f);
  template< class Functor >
  static Functor& ForEachR(Functor& f);

  std::ostream& inspect(std::ostream&) const;
};

}} // namespace

#endif /* #ifndef GIGLGU_LOGGING_LOGCONDITION_H */
