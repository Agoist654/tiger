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

  void Renamer::operator()(ast::FunctionDec& e)
  {
    visit(e, &e);
  }


  void Renamer::operator()(ast::TypeDec& e)
  {
    visit(e, &e);
  }

  void Renamer::operator()(ast::VarDec& e)
  {
    visit(e, &e);
  }

  void Renamer::operator()(ast::NameTy& e)
  {
      //name_set(typescope_.get_vector().get_back_map()->first)
      visit(e,e.def_get());
  }

  void Renamer::operator()(ast::SimpleVar& e)
  {
      visit(e,e.def_get());
  }

  void Renamer::operator()(ast::CallExp& e)
  {
    //because of recursive

//    super_type::operator()(e);
    visit(e, e.def_get());
  }

} // namespace bind
