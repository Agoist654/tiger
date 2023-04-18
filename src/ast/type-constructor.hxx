/**
 ** \file ast/type-constructor.hxx
 ** \brief Inline methods of ast::TypeConstructor.
 */

#pragma once

#include <ast/type-constructor.hh>
#include <type/types.hh>

namespace ast
{
  // FIXME: Some code was deleted here.

    type::Type* type_get() const
    {
        return type_;
    }

    const type::Type* type_get() const 
    {
        return type_;
    }

    void type_set()
    {
        return type_;
    }

} // namespace ast
