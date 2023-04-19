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

      auto tmp = forvector_;
      forvector_.clear();

      if (e.name_get() == "_main" && Binder::nb_main == 1)
      {
          redefinition(*funscope_.get_back_map().find("_main")->second, e);
      }

      if (nb_main == 0 && e.name_get() == "_main")
          Binder::nb_main = 1;

      forvector_ = tmp;
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
      auto tmp = forvector_;
      forvector_.clear();

      // FIXME: Some code was deleted here.
      scope_begin();
      super_type::operator()(*e.decs_get());
      if (e.body_get())
      super_type::operator()(*e.body_get());
      scope_end();

      forvector_ = tmp;
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
      auto tmp = forvector_;
      forvector_.clear();
      e.def_set(&e);
      varscope_.put(e.name_get(), &e);
      forvector_ = tmp;
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
          if (e.name_get() != "int" && e.name_get() != "string" && e.name_get() != "Object")
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
      operator()(e.hi_get());
      operator()(e.vardec_get());
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

    if (nb_main != 1)
    {
        error_ << misc::error::error_type::bind << "undeclared main" << "\n";
        error_.exit();
    }
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

  /*--------------------.
  | Visiting Objects.   |
  `--------------------*/
    

    void Binder::operator()(ast::ObjectExp& e)
    {
        if(typescope_.get_back_map().contains(e.type_name_get()->name_get()))
        {
            e.def_set(typescope_.get_back_map().find(e.type_name_get()->name_get())->second);
        }
        else
        {
             //undeclared("undeclared class", e);

        }
    }

    void Binder::operator()(ast::ClassTy& e)
    {
        classvector_.emplace_back(e.def_get());
        operator()(e.super_get());
        operator()(e.chunks_get());
        classvector_.pop_back();


    }


} // namespace bind
