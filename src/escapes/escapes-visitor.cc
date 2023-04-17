/**
 ** \file escapes/escapes-visitor.cc
 ** \brief Implementation for escapes/escapes-visitor.hh.
 */

#include <ast/all.hh>
#include <escapes/escapes-visitor.hh>
#include <misc/contract.hh>

namespace escapes
{
  // FIXME: Some code was deleted here.


    void EscapesVisitor::operator()(ast::VarDec& e)
    {
            vars_[&e] = funvector_.back();
            //std::cout << "vardec set to 0:" << e.name_get() << "\n";
            e.escape_set(0);
    }

    void EscapesVisitor::operator()(ast::FunctionDec& e)
    {

        funvector_.push_back(&e);
        super_type::operator()(e);

        for (auto args : e.formals_get())
        {
            //std::cout << "formals set to 0:" << args->name_get()<< "\n";
            //args->escape_set(0);
            vars_.erase(args);
        }

        funvector_.pop_back();
    }

    void EscapesVisitor::operator()(ast::SimpleVar& e)
    {
        if (vars_.find(e.def_get())->second != funvector_.back())
        {
            //std::cout << "simplevar set to 1:" << e.name_get()<< "\n";
            e.def_get()->escape_set(1);
        }
    }
} // namespace escapes
