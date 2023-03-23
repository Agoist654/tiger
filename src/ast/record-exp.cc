/**
 ** \file ast/record-exp.cc
 ** \brief Implementation of ast::RecordExp.
 */

#include <ast/record-exp.hh>
#include <ast/visitor.hh>
#include <misc/algorithm.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  /*DONE*/
  RecordExp::RecordExp(const Location& location, NameTy* type_name, fieldinits_type* fields)
          : Exp(location)
          , type_name_(type_name)
          , fields_(fields)
  {}

    void RecordExp::accept(ConstVisitor& v) const { v(*this); }

    void RecordExp::accept(Visitor& v) { v(*this); }
} // namespace ast
