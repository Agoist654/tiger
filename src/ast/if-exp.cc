/**
 ** \file ast/if-exp.cc
 ** \brief Implementation of ast::IfExp.
 */

#include <ast/if-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  /*DONE*/
  IfExp::IfExp(const Location& location, Exp* test, Exp* thenclause, Exp* elseclause = nullptr)
          : Exp(location)
          , test_(test)
          , thenclause_(thenclause)
          , elseclause_(elseclause)
  {}

  void IfExp::accept(ConstVisitor& v) const { v(*this); }

  void IfExp::accept(Visitor& v) { v(*this); }
} // namespace ast
