/**
 ** \file overload/type-checker.cc
 ** \brief Implementation for overload/type-checker.hh.
 */

#include <algorithm>
#include <sstream>

#include <misc/indent.hh>
#include <overload/type-checker.hh>
#include <type/types.hh>

namespace overload
{
  TypeChecker::TypeChecker(const overfun_bindings_type& overfun_bindings)
    : overfun_bindings_{overfun_bindings}
  {}

  const overfun_bindings_type& TypeChecker::overfun_bindings_get()
  {
      return overfun_bindings_;
  }


  bool TypeChecker::check_types(const ast::Ast& ast,
                                const std::string& exp1,
                                const type::Type& type1,
                                const std::string& exp2,
                                const type::Type& type2)
  {
    // FIXME: Some code was deleted here (Check for type mismatch).

  if (!type1.compatible_with(type2))
  {
      return false;
  }

    // If any of the type is Nil, set its `record_type_` to the other type.
    if (!error_)
      {
        // FIXME: Some code was deleted here.
        if(dynamic_cast<const type::Nil*>(&type1) != nullptr)
            dynamic_cast<const type::Nil*>(&type1)->record_type_set(type2);
        else if(dynamic_cast<const type::Nil*>(&type2) != nullptr)
            dynamic_cast<const type::Nil*>(&type2)->record_type_set(type1);

      }
    return true;
  }

  bool TypeChecker::check_types(const ast::Ast& ast,
                                const std::string& exp1,
                                ast::Typable& type1,
                                const std::string& exp2,
                                ast::Typable& type2)
  {
    // Ensure evaluation order.
    type(type1);
    type(type2);
    // FIXME: Some code was deleted here (Check types).

    bool res = check_types(ast, exp1, *type1.type_get(), exp2, *type2.type_get());
    res;
  }

  // FIXME: Some code was deleted here.
  void TypeChecker::operator()(ast::CallExp& e)
  {
      auto range = overfun_bindings_get().equal_range(&e);
      for (auto it = range.first; it != range.second; it++)
      {
        auto k = 0;
        if (it->second->formals_get().decs_get().size() != e.args_get()->size())
        {
            continue;
        }

        for (auto arg : it->second->formals_get())
        {
           bool match = check_types(e, "argument in call exp is not matching the function declaration: ", *arg, "given arg:", *e.args_get()->at(k++));
           if (!match)
                continue;

        }

        if(e.def_get() == nullptr)
        {
            e.def_set(it->second);
            type_default(e, e.def_get()->type_get());
        }

        else
        {
            //if(check_types(e, "", *e.args_get()->at(k++)), "", e.def_get()->
            error(e, "redef or ambiguity");
        }
      }

      //super_type::operator(e);
  }

/*
  template <class D> void TypeChecker::chunk_visit(ast::Chunk<D>& e)
    {
    // FIXME: Some code was deleted here.

    // Shorthand.
    using chunk_type = ast::Chunk<D>;
    super_type::operator()(e);
    // FIXME: Some code was deleted here (Two passes: once on headers, then on bodies).
    //std::map<misc::symbol, D*> m;

    for (auto& dec1 : e.decs_get())
    {
        for (auto& dec2 : e.decs_get())
        {

            if(dec1 != dec2 && dec1.name_get() == dec2.name_get())
            {
                if(dec1.result_get() && dec2.result_get() && check_types(e, "", dec1.result_get(), "", dec2.result_get()))
                {
                    if (dec1.formals_get().decs_get().size() != dec2.formals_get()->size())
                        {
                            continue;
                        }

                    for (auto arg1 : dec1.formals_get())
                    {
    
                        for (auto arg2 : dec2.formals_get())
                        {
                            bool match = check_types(e, "argument in call exp is not matching the function declaration: ", arg1, "given arg:", arg2;
                            if (match)
                                error(e, "redefinition in function chunk");

                        }

                }
           }

        }

    }


  }*/



} // namespace overload
