/**
 ** \file type/array.cc
 ** \brief Implementation for type/array.hh.
 */

#include <type/array.hh>
#include <type/visitor.hh>

namespace type
{
  // FIXME: Some code was deleted here.
  bool compatible_with(const Type& other)
  {
      return this->actual() == other;
  }

} // namespace type
