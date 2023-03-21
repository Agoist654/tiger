/**
 ** \file ast/assign-exp.hh
 ** \brief Declaration of ast::AssignExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/var.hh>

namespace ast {
    /// AssignExp.
    class AssignExp : public Exp {
        // FIXME: Some code was deleted here.
        /*DONE*/
    public:
        AssignExp(const Location& location, Var* var, Exp* exp);
        AssignExp(const AssignExp&) = delete;
        AssignExp& operator=(const AssignExp&) = delete;

        void accept(ConstVisitor& v) const override;
        void accept(Visitor& v) override;


        Var* var_get() const;
        Exp* exp_get() const;

    protected:
        Var* var_;
        Exp* exp_;
    };
} // namespace ast
#include <ast/assign-exp.hxx>
