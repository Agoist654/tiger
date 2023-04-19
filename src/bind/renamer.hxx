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
    template <> inline misc::symbol Renamer::new_name_compute(const ast::FunctionDec& e)
    {
        misc::symbol new_name = e.name_get();
        //if (dynamic_cast<const ast::Dec*>(&e) != nullptr)
        if(e.name_get().get().at(0) != '_' && e.body_get() != nullptr)
        {
           
            new_name = misc::symbol::fresh(e.name_get());
            //new_names_set(e, new_name);
        }
        new_names_set(e, new_name);

        return new_name;
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
        {
            if(def != nullptr)
            {
                misc::symbol new_name = new_name_compute(*def);
                e.name_set(new_name);
            }
        }
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
