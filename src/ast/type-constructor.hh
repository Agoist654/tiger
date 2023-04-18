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
    type::Type* typec_get() const;
    const type::Type* typec_get() const;

    void typec_set();

    protected:
    type::Type* typec_;
  };
} // namespace ast
#include <ast/type-constructor.hxx>
