/**
 ** \file ast/typable.hxx
 ** \brief Inline methods of ast::Typable.
 */

#pragma once

#include <ast/typable.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  inline Typable(type::Type* t): type_(t) {}
  void setType(type::Type* t)
  {
       type_ = t;
  }
  type::Type* getType() const
  {
       return type_;
  }
} // namespace ast
