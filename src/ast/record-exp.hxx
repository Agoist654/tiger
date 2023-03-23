/**
 ** \file ast/record-exp.hxx
 ** \brief Inline methods of ast::RecordExp.
 */

#pragma once

#include <ast/record-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  /*DONE*/
  inline NameTy* RecordExp::type_name_get() const { return type_name_; }
  inline fieldinits_type* RecordExp::fields_get() const { return fields_; }
} // namespace ast
