/**
 ** \file bind/renamer.cc
 ** \brief Implementation of bind::Renamer.
 */

#include <bind/renamer.hh>

namespace bind
{
  using namespace ast;

  Renamer::Renamer()
    : super_type()
    , new_names_()
  {}

  // FIXME: Some code was deleted here.

  void Renamer::scope_begin()
  {
      /*if (varscope_.get_vector().size() != 0)
          varscope_.get_vector().push_back(varscope_.get_vector().back());
      if (funscope_.get_vector().size() != 0)
          funscope_.get_vector().push_back(funscope_.get_vector().back());
      if (typescope_.get_vector().size() != 0)
          typescope_.get_vector().push_back(typescope_.get_vector().back());*/ //push n'est pas coder dans scoped_map
        varscope_.scope_begin();
        funscope_.scope_begin();
        typescope_.scope_begin();


  }

  void Renamer::scope_end()
  {
      if (varscope_.get_vector().size() != 0)
          varscope_.get_vector().pop_back();
      if (funscope_.get_vector().size() != 0)
          funscope_.get_vector().pop_back();
      if (typescope_.get_vector().size() != 0)
          typescope_.get_vector().pop_back(); //push n'est pas coder dans scoped_map
        /*varscope_.scope_end();
        funscope_.scope_end();
        typescope_.scope_end();*/

  }

  void compute_put_map(ast::VarDec* e)
  {
    varscope_.put(e.name_get(), &e);
  }

  void compute_put_map(ast::FunctionDec* e)
  {
    misc::symbol new_name = new_name_compute(e.name_get);
    new_name_get()[e] = new_name;
    funscope_.put(e.name_get(), &e);
  }


  void compute_put_map(ast::TypeDec* e)
  {
    misc::symbol new_name = new_name_compute(e.name_get);
    new_name_get()[e] = new_name;
    typescope_.put(e.name_get(), &e);
  }


  /*process*/
  void operator()(ast::CallExp& e)
  {
    //because of recursive

    super_type::operator()(e);
  }


  void operator()(ast::FunctionDec& e)
  {
      compute_put_map(e);
  }


  void operator()(ast::TypeDec& e)
  {
      compute_put_map(e);
  }

  void operator()(ast::VarDec& e)
  {
      compute_put_map(e);
  }

  void operator()(ast::NameTy& e)
  {
      name_set(typescope_.get_vector().get_back_map()->first)
  }

  void operator()(ast::SimpleVar& e)
  {}

  void operator()(ast::ChunkList & e)
  {}

  void operator()(ast::TypeChunk& e)
  {}

  void operator()(ast::VarChunk& e)
  {
  }

  void operator()(ast::FunctionChunk& e)
  {}

} // namespace bind
