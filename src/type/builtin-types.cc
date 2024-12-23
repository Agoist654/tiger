/**
 ** \file type/builtin-types.cc
 ** \brief Implementation for type/builtin-types.hh.
 */

#include <ostream>

#include <type/builtin-types.hh>
#include <type/visitor.hh>

namespace type
{
  // FIXME: Some code was deleted here (Int, String, Void).
  void String::accept(ConstVisitor& v) const { v(*this); }

  void String::accept(Visitor& v) { v(*this); }

  void Int::accept(ConstVisitor& v) const { v(*this); }

  void Int::accept(Visitor& v) { v(*this); }

  bool Int::compatible_with(const Type& other) { return *this == other || dynamic_cast<const Int*>(&other); }

  void Void::accept(ConstVisitor& v) const { v(*this); }

  void Void::accept(Visitor& v) { v(*this); }
} // namespace type
