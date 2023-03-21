/**
 ** \file ast/let-exp.hxx
 ** \brief Inline methods of ast::LetExp.
 */

#pragma once

#include <ast/let-exp.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  /*DONE*/
  inline ChunkList* LetExp::decs_get() const { return decs_; }
  inline Exp* LetExp::body_get() const { return body_; }
} // namespace ast
