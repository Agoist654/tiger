/**
 ** \file ast/if-exp.hh
 ** \brief Declaration of ast::IfExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/seq-exp.hh>

namespace ast
{
  /// IfExp.
  class IfExp : public Exp
  {
    // FIXME: Some code was deleted here.
    /*DONE*/
  public:
      IfExp(const Location& location, Exp* test, Exp* thenclause, Exp* elseclause);
      IfExp(const IfExp&) = delete;
      IfExp& operator=(const IfExp&) = delete;

      void accept(ConstVisitor& v) const override;
      void accept(Visitor& v) override;


      Exp* test_get() const;
      Exp* thenclause_get() const;
      Exp* elseclause_get() const;

  protected:
      Exp* test_;
      Exp* thenclause_;
      Exp* elseclause_;
  };
} // namespace ast
#include <ast/if-exp.hxx>
