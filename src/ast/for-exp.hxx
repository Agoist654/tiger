/**
 ** \file ast/for-exp.hxx
 ** \brief Inline methods of ast::ForExp.
 */

#pragma once

#include <ast/for-exp.hh>

namespace ast
{

  inline const VarDec& ForExp::vardec_get() const { return *vardec_; }
  inline VarDec& ForExp::vardec_get() { return *vardec_; }

  inline const Exp& ForExp::hi_get() const { return *hi_; }
  inline Exp& ForExp::hi_get() { return *hi_; }

  inline const Exp& ForExp::body_get() const { return *body_; }
  inline Exp& ForExp::body_get() { return *body_; }

  inline const Exp* ForExp::def_get() const { return def_; }
  inline Exp* ForExp::def_get() { return def_; }
  inline void ForExp::def_set(Exp* def) { def_ = def; }

} // namespace ast
