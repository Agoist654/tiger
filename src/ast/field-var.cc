/**
 ** \file ast/field-var.cc
 ** \brief Implementation of ast::FieldVar.
 */

#include <ast/field-var.hh>
#include <ast/visitor.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  /*DONE*/
  FieldVar::FieldVar(const Location& location,  Var* var, misc::symbol name)
          : Var(location)
          , var_(var)
          , name_(name)
  {}

    void FieldVar::accept(ConstVisitor& v) const { v(*this); }

    void FieldVar::accept(Visitor& v) { v(*this); }
} // namespace ast
