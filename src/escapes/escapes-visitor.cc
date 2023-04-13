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
            vars_[&e] = e.name_get();
    }


    void EscapesVisitor::operator()(ast::FunctionDec& e)
    {
        for ()
        super_type::operator()(e.formals_get());

        for (auto args : e.formals_get())
        {
            args->escape_set(0);
            vars_.erase(args);
        }

        if (e.result_get() != nullptr)
            super_type::operator()(e.result_get());
        if (e.body_get() != nullptr)
            super_type::operator()(e.body_get());

        in_function = 0;
    }

    void EscapesVisitor::operator()(ast::SimpleVar& e)
    {
        if (in_function == 0)
        {
            if (vars_.contains(e.def_get()))
            {
                e.def_get()->escape_set(0);
            }
        }
    }
} // namespace escapes
