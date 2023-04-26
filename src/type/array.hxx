/**
 ** \file type/array.hxx
 ** \brief Inline methods for type::Array.
 */
//#pragma once

#include <misc/contract.hh>
#include <type/array.hh>

namespace type
{
  // FIXME: Some code was deleted here.
  inline void Array::arrtype_set(const Type& type)
  {
      *arrtype_ = type;
  }
  inline Type* Array::arrtype_get() const
  {
     return arrtype_;
  }
} // namespace type
