/**
 ** \file ast/typable.hxx
 ** \brief Inline methods of ast::Typable.
 */

#pragma once

#include <ast/typable.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline Typable::typable(type::Type* t): type_(t) {}
  void Typable::setType(type::Type* t)
  {
       type_ = t;
  }
  type::Type* Typable::getType() const
  {
       return type_;
  }
} // namespace ast
