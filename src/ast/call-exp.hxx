/**
 ** \file ast/call-exp.hxx
 ** \brief Inline methods of ast::CallExp.
 */

#pragma once

#include <ast/call-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  /*DONE*/
  inline misc::symbol CallExp::name_get() const { return name_; }
  inline exps_type* CallExp::args_get() const { return args_; }
} // namespace ast
