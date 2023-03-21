/**
 ** \file ast/string-exp.cc
 ** \brief Implementation of ast::StringExp.
 */

#include <ast/string-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  // FIXME: Some code was deleted here.
  /*DONE*/
  StringExp::StringExp(const Location& location, std::string value)
          : Exp(location)
          , value_(value)
  {}

    void StringExp::accept(ConstVisitor& v) const { v(*this); }

    void StringExp::accept(Visitor& v) { v(*this); }
} // namespace ast
