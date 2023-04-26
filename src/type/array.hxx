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
  inline Type& Array::arrtype_get()
  {
      return *arrtype_;
  }

  inline void Array::arrtype_set(const Type& type)
  {
      *arrtype_ = type;
  }


  inline void Array::arrtype_set(Type& type)
  {
      *arrtype_ = type;
  }

  inline Type* Array::arrtype_get() const
  {
     return arrtype_;
  }

  inline void Array::accept(Visitor& v)
  {
      v(*this);
  }
  inline void Array::accept(ConstVisitor& v) const
  {
      v(*this);
  }

} // namespace type
