/*
 * $Id: BitName.h 267 2012-05-18 16:04:51Z alba $
 *
 * Copyright 2012 Alexander Bartolich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef GIGLGU_PLAINTEXT_BITNAME_H
#define GIGLGU_PLAINTEXT_BITNAME_H

#include <giglgu/plaintext/Component.h>

#include <iostream>	// std::ostream
#include <iomanip>	// std::hex

namespace giglgu { namespace PlainText {

template<class ValueT, class DstStreamT, class SrcStringT>
struct BitName
{
  ValueT bitValue;
  SrcStringT bitName;
  
  typedef const BitName<ValueT, DstStreamT, SrcStringT>* ConstIterator;

  /**
   * @param this
   * Points to first element of a zero-terminated array of FlagValue
   * instances.
   * @param dst
   * The stream to write the output into.
   * @param value
   * The bit mask to decode.
   * @param separator
   * This string is written between elements of the bit mask.
   */
  void decode(
    DstStreamT& dst,
    ValueT value,
    const SrcStringT& separator
  ) const;
};

template<class ValueT, class DstStreamT, class SrcStringT>
void BitName<ValueT, DstStreamT, SrcStringT>::decode
  (DstStreamT& dst, ValueT value, const SrcStringT& separator)
  const
{
  if (value == 0)
  {
    dst << '0';
    return;
  }
  for(ConstIterator fv = this; fv->bitName != 0; ++fv)
  {
    if ((value & fv->bitValue) == fv->bitValue)
    {
      dst << fv->bitName;
      value &= ~fv->bitValue;
      if (value == 0)
        return;
      else
        dst << separator;
    }
  }
  if (value != 0)
  {
    dst << "0x" << std::hex << value << std::dec;
  }
}  
  
typedef GIGLGU_PLAINTEXT_EXPORT_TEMPLATE
  BitName<unsigned, std::ostream, const char*> BasicBitName;

}} // namespace

#endif
