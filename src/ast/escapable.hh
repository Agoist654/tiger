/**
 ** \file ast/escapable.hh
 ** \brief Declaration of ast::Escapable.
 */

#pragma once

#include <ast/fwd.hh>

namespace ast
{
 // Escapable.
 class Escapable
  {
     //FIXME: Some code was deleted here

      public:
          Escapable();
          Escapable(const Escapable&) = delete;
          Escapable& operator=(const Escapable&) = delete;

          int escape_get();
          const int escape_get() const;
          void escape_set(int escape);

//          void operator()(const VarDec) override;

      protected:
          /*luca veut un bool*/
          int escape_ = 1;

  };
}//  namespace ast
#include <ast/escapable.hxx>
