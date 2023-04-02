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
  void redefinition(const T& e1, const T& e2)
  {
     {
	std::cerr << "redefinition: " << e1 << std::endl;
	std::cerr << "first definition: " << e2 << std::endl; //regarder tp.error_ de scantiger.ll
     }// utiliser misc::error
  }
  void error(const ast::Ast& loc, const std::string& msg);
  void check_main(const ast::FunctionDec& e);
  template <typename T> void undeclared(const std::string& k, const T& e);



  /*----------------------------.
  | Visiting /ChunkInterface/.  |
  `----------------------------*/

  template <class D> void Binder::chunk_visit(ast::Chunk<D>& e)
  {
    // Shorthand.
    using chunk_type = ast::Chunk<D>;
    // FIXME: Some code was deleted here (Two passes: once on headers, then on bodies).
    scope_begin();
    for (auto& dec : e.declarations) 
    {
        visit(dec);
    }
    visit(e.body);
    scope_end();
  }

  /* These specializations are in bind/binder.hxx, so that derived
     visitors can use them (otherwise, they wouldn't see them).  */

  // Insert the prototype of the function in the environment.
  template <>
  inline void Binder::visit_dec_header<ast::FunctionDec>(ast::FunctionDec& e)
  {
    // FIXME: Some code was deleted here.
    auto fd = funscope_.get(e.name_get());
    //use visit_chunk at e.formal
    if (fd == nullptr) // on check si les formals de FunctionDec existe deja dans notre scop 
    {
	  //error ici je rajoute juste des fonction 
    	funscope_.put(e.name_get(), e);
    }
  }

  // Compute the bindings of this function's body.
  template <>
  inline void Binder::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e)
  {
    // FIXME: Some code was deleted here.
    scope_begin();
    e.formals_get().accept(*this);
    e.result_get()->accept(*this);
    e.body_get()->accept(*this);
    scope_end();
  }

} // namespace bind
