/**
 ** \file ast/assign-exp.hxx
 ** \brief Inline methods of ast::AssignExp.
 */

#pragma once

#include <ast/assign-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  /*DONE*/
  inline Var* AssignExp::var_get() const { return var_; }
  inline Exp* AssignExp::exp_get() const { return exp_; }
} // namespace ast
