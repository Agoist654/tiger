/**
 ** \file ast/method-call-exp.hxx
 ** \brief Inline methods of ast::MethodCallExp.
 */

#pragma once

#include <ast/method-call-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  /*DONE*/
  inline misc::symbol MethodCallExp::name_get() const { return name_; }
  inline exps_type* MethodCallExp::args_get() const { return args_; }
  inline Var* MethodCallExp::object_get() const { return object_; }
} // namespace ast
