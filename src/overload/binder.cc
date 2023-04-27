/**
 ** \file overload/binder.cc
 ** \brief Implementation of overload::Binder.
 */

#include <ast/all.hh>
#include <overload/binder.hh>

namespace overload
{
  overfun_bindings_type& Binder::overfun_bindings_get()
  {
    return overfun_bindings_;
  }

  /*---------.
  | Scopes.  |
  `---------*/

  void Binder::scope_begin()
  {
    super_type::scope_begin();
    overfuns_.scope_begin();
  }

  void Binder::scope_end()
  {
    overfuns_.scope_end();
    super_type::scope_end();
  }

  /*-------------------.
  | Visiting methods.  |
  `-------------------*/

  // Same as Binder's, but do not set the definition site of E.
  void Binder::operator()(ast::CallExp& e)
  {
    // FIXME: Some code was deleted here.
    if (!funscope_.get_back_map().contains(e.name_get()))
      {
          undeclared("undeclared function:", e);
      }

    else
      {
          //e.def_set(funscope_.get_back_map().find(e.name_get())->second);
          if (e.args_get())
          {
              for (auto& v : *e.args_get())
              {
                  super_type::operator()(v);
              }
          }
      }


  }

  // Insert the prototype of the function in the environment.
  void Binder::visit_dec_header(ast::FunctionDec& e)
  {
    check_main(e);
    overfuns_.put(e.name_get(), e);
  }

  void Binder::operator()(ast::FunctionChunk& e)
  {
    // Two passes: once on headers, then on bodies.
    // FIXME: Some code was deleted here.;
    // FIXME: Some code was deleted here (Two passes: once on headers, then on bodies).
    std::map<misc::symbol, ast::FunctionDec*> m;

    for (auto& dec : e.decs_get())
    {
        if (m.contains(dec->name_get()))
        {
            //check_main(e);
            //redefinition(*m.find(dec->name_get())->second, *dec);
            //return;
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

} // namespace overload
