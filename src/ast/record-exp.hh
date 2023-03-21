/**
 ** \file ast/record-exp.hh
 ** \brief Declaration of ast::RecordExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/field-init.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// RecordExp.
  class RecordExp : public Exp
  {
    // FIXME: Some code was deleted here.
    /*DONE*/
  public:
      RecordExp(const Location& location, NameTy* type_name, fieldinits_type* fields);
      RecordExp(const RecordExp&) = delete;
      RecordExp& operator=(const RecordExp&) = delete;

      void accept(ConstVisitor& v) const override;
      void accept(Visitor& v) override;


      NameTy* type_name_get() const;
      fieldinits_type* fields_get() const;

  protected:
      NameTy* type_name_;
      fieldinits_type* fields_;
  };
} // namespace ast
#include <ast/record-exp.hxx>
