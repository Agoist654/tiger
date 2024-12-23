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

    /*type::Type* TypeConstructor::type_constructor_get() const
    {
        return type_constructor_;
    }*/

    inline const type::Type* TypeConstructor::type_constructor_get() const
    {
        return type_constructor_;
    }

    inline void TypeConstructor::type_constructor_set(const type::Type* type)
    {
        type_constructor_ = type;
    }


    inline void TypeConstructor::type_constructor_set(type::Type* type)
    {
        type_constructor_ = type;
    }

} // namespace ast
