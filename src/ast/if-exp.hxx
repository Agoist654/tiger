/**
 ** \file ast/if-exp.hxx
 ** \brief Inline methods of ast::IfExp.
 */

#pragma once

#include <ast/if-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  /*DONE*/
  inline Exp* IfExp::test_get() const { return test_; }
  inline Exp* IfExp::thenclause_get() const { return thenclause_; }
  inline Exp* IfExp::elseclause_get() const { return elseclause_; }
} // namespace ast
