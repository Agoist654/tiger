/**
 ** \file ast/break-exp.hh
 ** \brief Declaration of ast::BreakExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{
  /// BreakExp.
  class BreakExp : public Exp
  {
    // FIXME: Some code was deleted here.
    /*DONE*/
  public:
      BreakExp(const Location& location);
      BreakExp(const BreakExp&) = delete;
      BreakExp& operator=(const BreakExp&) = delete;

      void accept(ConstVisitor& v) const override;
      void accept(Visitor& v) override;

      const Exp* def_get() const;
      Exp* def_get();
      void def_set(Exp* def);

  protected:
      Exp* def_ = nullptr;

  };

} // namespace ast
#include <ast/break-exp.hxx>
