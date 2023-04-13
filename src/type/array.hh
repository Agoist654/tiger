/**
 ** \file type/array.hh
 ** \brief The class Array.
 */
#pragma once

#include <type/fwd.hh>
#include <type/type.hh>

namespace type
{
  /// Array types.
  class Array : public Type
  {
    // FIXME: Some code was deleted here.
  public:
      Type arrtype_get();
      void arrtype_set(const Type& type);
      bool compatible_with(const Type& other) const override;
      void accept(ConstVisitor& v) const override;

  protected:
      Type* arrtype_;
  };

} // namespace type

#include <type/array.hxx>
