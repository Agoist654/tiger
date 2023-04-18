/**
 ** \file ast/object-exp.hxx
 ** \brief Inline methods of ast::ObjectExp.
 */

#pragma once

#include <ast/object-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  /*DONE*/
  inline NameTy* ObjectExp::type_name_get() const { return type_name_; }
  inline const TypeDec* ObjectExp::def_get() const { return def_; }
  inline TypeDec* ObjectExp::def_get() { return def_; }
  inline void ObjectExp::def_set(TypeDec* def) { def_ = def; }



} // namespace ast
