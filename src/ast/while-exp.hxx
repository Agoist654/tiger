/**
 ** \file ast/while-exp.hxx
 ** \brief Inline methods of ast::WhileExp.
 */

#pragma once

#include <ast/while-exp.hh>

namespace ast
{

  inline const Exp& WhileExp::test_get() const { return *test_; }
  inline Exp& WhileExp::test_get() { return *test_; }

  inline const Exp& WhileExp::body_get() const { return *body_; }
  inline Exp& WhileExp::body_get() { return *body_; }

  inline const Exp* WhileExp::def_get() const { return def_; }
  inline Exp* WhileExp::def_get() { return def_; }
  inline void WhileExp::def_set(Exp* def) { def_ = def; }

} // namespace ast
