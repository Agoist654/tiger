/**
 ** \file ast/seq-exp.hh
 ** \brief Declaration of ast::SeqExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{
  /// SeqExp.
  class SeqExp : public Exp
  {
    // FIXME: Some code was deleted here.
    /*DONE*/
  public:
      SeqExp(const Location& location, exps_type* exps);
      SeqExp(const SeqExp&) = delete;
      SeqExp& operator=(const SeqExp&) = delete;

      void accept(ConstVisitor& v) const override;
      void accept(Visitor& v) override;


      exps_type* exps_get() const;

  protected:
      exps_type* exps_;
  };
} // namespace ast
#include <ast/seq-exp.hxx>
