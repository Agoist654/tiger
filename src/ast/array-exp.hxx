/**
 ** \file ast/array-exp.hxx
 ** \brief Inline methods of ast::ArrayExp.
 */

#pragma once

#include <ast/array-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  /*DONE*/
  inline NameTy* ArrayExp::Type_name_get() const { return type_name_; }
  inline Exp* ArrayExp::size_get() const { return size_; }
  inline Exp* ArrayExp::init_get() const { return init_; }
} // namespace ast
