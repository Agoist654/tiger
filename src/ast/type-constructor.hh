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
    TypeConstructor(type::Type* t) : type_(t) {}
    type::Type* getType() const 
    {
        return type_;
    }
    private:
    type::Type* type_;
  };
} // namespace ast
#include <ast/type-constructor.hxx>
