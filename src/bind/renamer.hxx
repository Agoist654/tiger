/**
 ** \file bind/renamer.hxx
 ** \brief Template methods of bind::Renamer.
 */

#pragma once

#include <bind/renamer.hh>

namespace bind
{
    using new_names_type = std::map<const ast::Dec*, misc::symbol>;
  // FIXME: Some code was deleted here.
  template <typename Def> misc::symbol new_name_compute(const Def& e)
  {
      if (e->name_get() == "_main") //TODO: add primitive case later
          return e->name_get();
      return misc::symbol::fresh(e->name_get());
  }
    
  /*
  template <typename Def> misc::symbol new_name(const Def& e)
  {
      return misc::fresh(e->name_get(()));
  }*/



  inline new_names_type new_names_get(){ return new_names_; }



  template <class E, class Def> void Renamer::visit(E& e, const Def* def)
  {
    // FIXME: Some code was deleted here.

      if (&e == def)
          misc::symbol new_name = new_name_compute(e.name_get);
      new_name_get()[e] = new_name;
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
    void Renamer::chunk_visit(ast::Chunk<D>& e)
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
            return;
        }
        m[dec->name_get()] = dec;
        visit_dec_header(*dec);
        //visit_dec_body(*dec);
    }

    for (auto& dec : e.decs_get())
    {
        visit_dec_body(*dec);
    }

  }


  /* These specializations are in bind/binder.hxx, so that derived
     visitors can use them (otherwise, they wouldn't see them).  */

  // Insert the prototype of the function in the environment.
  template <>
      inline void Renamer::visit_dec_header<ast::FunctionDec>(ast::FunctionDec& e)
      {
          // FIXME: Some code was deleted here.

          misc::symbol new_name = new_name_compute(e.name_get);
          new_name_get()[e] = new_name;
          funscope_.put(e.name_get(), &e);
      }

  // Compute the bindings of this function's body.
  template <>
      inline void Renamer::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e)
      {
          // FIXME: Some code was deleted here.
          scope_begin();
          super_type::operator()(e);
          scope_end();
      }

  template <>
      inline void Renamer::visit_dec_header<ast::TypeDec>(ast::TypeDec& e)
      {
          typescope_.put(e.name_get(), &e);
      }

  template <>
      inline void Renamer::visit_dec_body<ast::TypeDec>(ast::TypeDec& e)
      {
          e.ty_get().accept(*this);
      }

  template <>
  inline void Renamer::visit_dec_header<ast::VarDec>(ast::VarDec& e)
  {
      varscope_.put(e.name_get(), &e);
  }

  template <>
      inline void Renamer::visit_dec_body<ast::VarDec>(ast::VarDec& e)
      {
          super_type::operator()(e);
      }


} // namespace bind*/
