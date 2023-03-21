/**
 ** \file ast/array-exp.hh
 ** \brief Declaration of ast::ArrayExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// ArrayExp.
  class ArrayExp : public Exp
  {
    // FIXME: Some code was deleted here.
    /*DONE*/
  public:
      ArrayExp(const Location& location, NameTy* type_name, Exp* size, Exp* init);
      ArrayExp(const ArrayExp&) = delete;
      ArrayExp& operator=(const ArrayExp&) = delete;

      void accept(ConstVisitor& v) const override;
      void accept(Visitor& v) override;

      NameTy* Type_name_get() const;
      Exp* size_get() const;
      Exp* init_get() const;

  protected:
      NameTy* type_name_;
      Exp* size_;
      Exp* init_;
  };
} // namespace ast
#include <ast/array-exp.hxx>
