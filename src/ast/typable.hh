/**
 ** \file ast/typable.hh
 ** \brief Declaration of ast::Typable.
 */

#pragma once

#include <ast/fwd.hh>
#include <type/fwd.hh>

namespace ast
{
    /** \class ast::Typable
     ** \brief Hold a type information.
     **
     ** A Typable node holds a type information (type::Type) about
     ** this node.  This can be:
     ** \li the type of the node itself, if it is a Exp or a Ty, or
     ** \li the type of of the declared object, in case of a Dec.
     */

    class Typable
    {
        // FIXME: Some code was deleted he
    public:
        Typable()
            : type_(nullptr)
        {}
        inline Typable(type::Type* t)
            : type_(t)
        {}
        void setType(type::Type* t)
        {
            type_ = t;
        }
        type::Type* getType() const
        {
            return type_;
        }

    private:
        type::Type* type_;
    };
} // namespace ast
#include <ast/typable.hxx>
