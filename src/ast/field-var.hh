/**
 ** \file ast/field-var.hh
 ** \brief Declaration of ast::FieldVar.
 */

#pragma once

#include <ast/var.hh>
#include <misc/symbol.hh>

namespace ast
{
  /// FieldVar.
  class FieldVar : public Var
  {
    // FIXME: Some code was deleted here.
    /*DONE*/
  public:
      FieldVar(const Location& location, Var* var, misc::symbol name);
      FieldVar(const FieldVar&) = delete;
      FieldVar& operator=(const FieldVar&) = delete;

      void accept(ConstVisitor& v) const override;
      void accept(Visitor& v) override;


      Var* var_get() const;
      misc::symbol name_get() const;

  protected:
      Var* var_;
      misc::symbol name_;
  };
} // namespace ast
#include <ast/field-var.hxx>
