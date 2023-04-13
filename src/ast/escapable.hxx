/**
 ** \file ast/escapable.hxx
 ** \brief Inline methods of ast::Escapable.
 */

#pragma once

#include <ast/escapable.hh>

namespace ast
{
   //FIXME: Some code was deleted here.

    inline int Escapable::escape_get()
    { return escape_; }

    inline const int Escapable::escape_get() const
    { return escape_; }

    inline void Escapable::escape_set(int escape)
    { escape_ = escape; }

}  //namespace ast
