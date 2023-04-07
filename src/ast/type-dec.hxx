/**
 ** \file ast/type-dec.hxx
 ** \brief Inline methods of ast::TypeDec.
 */

#pragma once

#include <ast/type-dec.hh>

namespace ast
{

  inline const Ty& TypeDec::ty_get() const { return *ty_; }
  inline Ty& TypeDec::ty_get() { return *ty_; }


  inline const TypeDec* TypeDec::def_get() const { return def_; }
  inline TypeDec* TypeDec::def_get() { return def_; }
  inline void TypeDec::def_set(TypeDec* def) { def_ = def; }

} // namespace ast
