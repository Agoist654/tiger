/**
 ** \file ast/type-constructor.hh
 ** \brief Declaration of ast::TypeConstructor.
 */

#pragma once

#include <ast/fwd.hh>
#include <type/fwd.hh>

namespace ast
{
  /** \class ast::TypeConstructor
   ** \brief Create a new type.
   */

  class TypeConstructor
  {
    // FIXME: Some code was deleted here.
    public:

    TypeConstructor();
    //type::Type* type_constructor_get() const;
    const type::Type* type_constructor_get() const;

    void type_constructor_set(type::Type* type);

    protected:
    type::Type* type_constructor_;
  };
} // namespace ast
#include <ast/type-constructor.hxx>
