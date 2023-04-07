/**
 ** \file bind/binder.hxx
 ** \brief Inline methods of bind::Binder.
 **/

#pragma once

#include <bind/binder.hh>

namespace bind
{
  /*-----------------.
  | Error handling.  |
  `-----------------*/

    // FIXME: Some code was deleted here (Error reporting).
    template <typename T>
        inline void Binder::redefinition(const T& e1, const T& e2)
        {
            std::cout << "redef";
                error_ << misc::error::error_type::bind << "redefinition" << '\n';
                error_ << misc::error::error_type::bind << "first definition" << '\n';
        }


    template <typename T>
        inline void Binder::undeclared(const std::string& k, const T& e) 
        {
            error_ << /*meite e.loc_get() << ": undeclared identifier: "*/ 
            misc::error::error_type::bind << k;
        }



  /*----------------------------.
  | Visiting /ChunkInterface/.  |
  `----------------------------*/
    /*
    void GenDefaultVisitor<Const>::operator()(const_t<ChunkList>& e)
    {
        for ( auto& x : e.chunks_get())
            x->accept(*this);
    }*/

  template <class D>
    void Binder::chunk_visit(ast::Chunk<D>& e)
  {
    // Shorthand.
    using chunk_type = ast::Chunk<D>;
    // FIXME: Some code was deleted here (Two passes: once on headers, then on bodies).
    std::map<misc::symbol, D*> m;

    for (auto& dec : e.decs_get())
    {
        if (m.contains(dec->name_get()))
        {
            //check_main(e);
            redefinition(*m.find(dec->name_get())->second, *dec);
            std::cout << "test";
            //error noticed but not properly handled
            return;
        }
        m[dec->name_get()] = dec;
        visit_dec_header(*dec);
        visit_dec_body(*dec);
    }
  }


  /* These specializations are in bind/binder.hxx, so that derived
     visitors can use them (otherwise, they wouldn't see them).  */

  // Insert the prototype of the function in the environment.
  template <>
      inline void Binder::visit_dec_header<ast::FunctionDec>(ast::FunctionDec& e)
      {
          // FIXME: Some code was deleted here.
          check_main(e);
          funscope_.put(e.name_get(), &e);

          e.formals_get().accept(*this);
          if(e.result_get())
            e.result_get()->accept(*this);
      }

  // Compute the bindings of this function's body.
  template <>
      inline void Binder::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e)
      {
          // FIXME: Some code was deleted here.
          scope_begin();
          e.body_get()->accept(*this);
          scope_end();
      }

  template <>
      inline void Binder::visit_dec_header<ast::TypeDec>(ast::TypeDec& e)
      {
          typescope_.put(e.name_get(), &e);
      }

  template <>
      inline void Binder::visit_dec_body<ast::TypeDec>(ast::TypeDec& e)
      {
          e.ty_get().accept(*this);
      }


  template <>
  inline void Binder::visit_dec_header<ast::VarDec>(ast::VarDec& e)
  {
      varscope_.put(e.name_get(), &e);
  }

  template <>
      inline void Binder::visit_dec_body<ast::VarDec>(ast::VarDec& e)
      { 
          if(e.init_get())
            e.init_get()->accept(*this);
      }
} // namespace bind


