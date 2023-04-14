/**
 ** \file bind/binder.cc
 ** \brief Implementation for bind/binder.hh.
 */

#include <ast/all.hh>
#include <bind/binder.hh>

#include <misc/contract.hh>

namespace bind
{
  /*-----------------.
  | Error handling.  |
  `-----------------*/

  /// The error handler.
  const misc::error& Binder::error_get() const { return error_; }

  // FIXME: Some code was deleted here (Error reporting).

  void Binder::check_main(const ast::FunctionDec& e)
  {
      // FIXME: Some code was deleted here.

      if (e.name_get() == "_main" && nb_main == 1)
      {
          redefinition(*funscope_.get_back_map().find("_main")->second, e);
      }
      if (nb_main == 0 && e.name_get() == "_main")
          nb_main = 1;

  }

  /*----------------.
  | Symbol tables.  |
  `----------------*/

  void Binder::scope_begin()
  {
    // FIXME: Some code was deleted here.
        varscope_.scope_begin();
        funscope_.scope_begin();
        typescope_.scope_begin();


  }

  void Binder::scope_end()
  {
    // FIXME: Some code was deleted here.
        varscope_.scope_end();
        funscope_.scope_end();
        typescope_.scope_end();

  }

  /*---------.
  | Visits.  |
  `---------*/

  // FIXME: Some code was deleted here.
  void Binder::operator()(ast::LetExp& e)
  {
      // FIXME: Some code was deleted here.
      scope_begin();
      super_type::operator()(*e.decs_get());
      if (e.body_get())
      super_type::operator()(*e.body_get());
      scope_end();
  }

  // FIXME: Some code was deleted here.
  void Binder::operator()(ast::Ast& e)
  {
      super_type::operator()(e);
  }

  void Binder::operator()(ast::CallExp& e)
  {
      if (!funscope_.get_back_map().contains(e.name_get()))
      {
          undeclared("undeclared function:", e);
      }
      else
      {
          e.def_set(funscope_.get_back_map().find(e.name_get())->second);
          if (e.args_get())
          {
              for (auto& v : *e.args_get())
              {
                  super_type::operator()(v);
              }
          }
      }
  }

  void Binder::operator()(ast::VarDec& e)
  {
      e.def_set(&e);
      varscope_.put(e.name_get(), &e);
  }

  void Binder::operator()(ast::SimpleVar& e)
  {
      if (!varscope_.get_back_map().contains(e.name_get()))
      {
          undeclared("undeclared var: ", e.name_get());
          return;
      }

      e.def_set(varscope_.get_back_map().find(e.name_get())->second);
  }

  void Binder::operator()(ast::IfExp& e)
  {
      super_type::operator()(e);
  }

  void Binder::operator()(ast::TypeDec& e)
  {
      typescope_.put(e.name_get(), &e);
      e.def_set(&e);
  }

  void Binder::operator()(ast::NameTy& e)
  {
      if (typescope_.get_back_map().contains(e.name_get()))
      { 
          e.def_set(typescope_.get_back_map().find(e.name_get())->second);
      }

      else
      {
          if (e.name_get() != "int" && e.name_get() != "string")
          {
              undeclared("undeclared type", e);
          }

          else
              e.def_set(nullptr);
      }
  }

  void Binder::operator()(ast::ForExp& e)
  {
      scope_begin();
      e.def_set(&e);
      forvector_.emplace_back(&e);
      operator()(e.vardec_get());
      operator()(e.hi_get());
      super_type::operator()(e.body_get());

      scope_end();
      forvector_.pop_back();
  }

  void Binder::operator()(ast::WhileExp& e)
  {
      e.def_set(&e);
      forvector_.emplace_back(&e);
      super_type::operator()(e.body_get());
      forvector_.pop_back();
  }


  void Binder::operator()(ast::BreakExp& e)
  {
      if (forvector_.size() <= 0)
      {
        undeclared("break ouside any loop", e);
      }
      else
        {
          e.def_set(forvector_.back());
        }

  }


    void Binder::operator()(ast::ChunkList & e)
    {
        scope_begin();
        for ( auto& x : e.chunks_get())
            x->accept(*this);
    }
  /*-------------------.
  | Visiting VarChunk. |
  `-------------------*/


  void Binder::operator()(ast::VarChunk& e)
  {
      chunk_visit(e);
  }
  /*------------------------.
  | Visiting FunctionChunk. |
  `------------------------*/

  // FIXME: Some code was deleted here.
   void Binder::operator()(ast::FunctionChunk& e)
   {
      chunk_visit(e);
   }


  /*--------------------.
  | Visiting TypeChunk. |
  `--------------------*/
  // FIXME: Some code was deleted here.
  
  void Binder::operator()(ast::TypeChunk& e)
  {
      chunk_visit(e);
  }

} // namespace bind
