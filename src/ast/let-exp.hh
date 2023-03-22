/**
 ** \file ast/let-exp.hh
 ** \brief Declaration of ast::LetExp.
 */

#pragma once

#include <ast/chunk-list.hh>
#include <ast/exp.hh>
#include <misc/contract.hh>

namespace ast
{
  /// LetExp.
  class LetExp : public Exp
  {
    // FIXME: Some code was deleted here.
    /*DONE*/
  public:
      LetExp(const Location& location, ChunkList* decs, Exp* body);
      LetExp(const LetExp&) = delete;
      LetExp& operator=(const LetExp&) = delete;

      void accept(ConstVisitor& v) const override;

      void accept(Visitor& v) override;

      ChunkList* decs_get() const;
      Exp* body_get() const;
  protected:
      ChunkList* decs_;
      Exp* body_;
  };
} // namespace ast
#include <ast/let-exp.hxx>
