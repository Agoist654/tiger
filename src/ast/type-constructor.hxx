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

    type::Type* type_constructor_get() const
    {
        return type_constructor_;
    }

    const type::Type* type_constructor_get() const 
    {
        return type_constructor_;
    }

    void type_constructor_set()
    {
        return type_constructor_;
    }

} // namespace ast
