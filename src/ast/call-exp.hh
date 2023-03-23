/**
 ** \file ast/call-exp.hh
 ** \brief Declaration of ast::CallExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/function-dec.hh>
#include <misc/symbol.hh>

namespace ast
{
  /// CallExp.
  class CallExp : public Exp
  {
    // FIXME: Some code was deleted here.
    /*DONE*/
  public:
      CallExp(const Location& location, misc::symbol name, exps_type* args);
      CallExp(const CallExp&) = delete;
      CallExp& operator=(const CallExp&) = delete;

      void accept(ConstVisitor& v) const override;
      void accept(Visitor& v) override;

      misc::symbol name_get() const;
      exps_type* args_get() const;

  protected:
      misc::symbol name_;
      exps_type* args_;
  };
} // namespace ast
#include <ast/call-exp.hxx>
