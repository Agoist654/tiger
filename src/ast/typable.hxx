/**
 ** \file ast/typable.hxx
 ** \brief Inline methods of ast::Typable.
 */

#pragma once

#include <ast/typable.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline Typable::Typable(type::Type* t): type_(t) {};
  inline void Typable::type_set(type::Type* t)
  {
       type_ = t;
  }

  inline void Typable::type_set(const type::Type* t)
  {
       type_ = t;
  }

  inline type::Type* Typable::type_get() const
  {
       return type_;
  }
} // namespace ast
