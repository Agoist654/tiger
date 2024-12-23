/**
 ** \file type/array.cc
 ** \brief Implementation for type/array.hh.
 */

#include <type/array.hh>
//#include <type/visitor.hh>

namespace type
{
  // FIXME: Some code was deleted here.



  void Array::accept(Visitor& v)
  {
      v(*this);
  }
  void Array::accept(ConstVisitor& v) const
  {
      v(*this);
  }

} // namespace type
