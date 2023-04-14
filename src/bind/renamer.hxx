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

    template <typename Def> inline misc::symbol Renamer::new_name_compute(const Def& e)
    {
        misc::symbol new_name = misc::symbol::fresh(e.name_get());
        //if (dynamic_cast<const ast::Dec*>(&e) != nullptr)
            new_names_set(e, new_name);
        return new_name;
    }

    template <> inline misc::symbol Renamer::new_name_compute(const ast::CallExp& e)
    {

        misc::symbol new_name = misc::symbol::fresh(e.name_get());

        new_names_set(*dynamic_cast<const ast::CallExp*>(e.def_get()), new_name);

        return new_name;
    }

    template <> inline misc::symbol Renamer::new_name_compute(const ast::FunctionDec& e)
    {
        if (new_names_get().contains(&e))
        {
            return new_names_get().find((dynamic_cast<const ast::Dec*>(&e)))->second;
        }

        if (e.name_get() == "_main" || e.body_get() == nullptr) //TODO: add primitive case later
            return e.name_get();

        misc::symbol new_name = misc::symbol::fresh(e.name_get());

        if (dynamic_cast<const ast::Dec*>(&e) != nullptr)
            new_names_set(e, new_name);

        return new_name;
    }

    template <> inline misc::symbol Renamer::new_name_compute(const ast::NameTy& e)
    {
        if (e.name_get() == "string" || e.name_get() == "int" )
            return e.name_get();
        misc::symbol new_name = misc::symbol::fresh(e.name_get());
        if (dynamic_cast<const ast::Dec*>(&e) != nullptr)
            new_names_set(e, new_name);
        return new_name;
    }

    template <typename Def> inline misc::symbol Renamer::new_name(const Def& e)
    {
        if (dynamic_cast<const ast::Dec*>(&e) == nullptr)
        {
            if (new_names_get().contains(dynamic_cast<const ast::Dec*>(&e)))
            {
                if (e.def_get() != nullptr)
                    return new_names_get().find(e.def_get())->second;
            }
        }
        return new_name_compute(e);
    }

    inline new_names_type Renamer::new_names_get()
    {
        return new_names_;
    }

    template <typename Def>
    inline void Renamer::new_names_set(const Def& e, misc::symbol new_name)
    {
        new_names_[dynamic_cast<const ast::Dec*>(&e)] = new_name;
    }

    template <class E, class Def> inline void Renamer::visit(E& e, const Def* def)
    {
        // FIXME: Some code was deleted here.

        if (new_names_get().contains(def))
            e.name_set(new_names_get().find(def)->second);

        else
            e.name_set(new_name_compute(e));
        super_type::operator()(e);
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

} // namespace bind*/
