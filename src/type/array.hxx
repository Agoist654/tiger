/**
 ** \file type/array.hxx
 ** \brief Inline methods for type::Array.
 */
#pragma once

#include <misc/contract.hh>
#include <type/array.hh>

namespace type
{
  // FIXME: Some code was deleted here.
  Type Array::arrtype_get()
  {
      return *arrtype_;
  }

  void Array::arrtype_set(const Type& type)
  {
      *arrtype_ = type;
  }

  void Array::accept(ConstVisitor& v) const
  {
      v(*this);
  }

} // namespace type
