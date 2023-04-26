/**
 ** \file ast/object-visitor.hxx
 ** \brief Implementation for ast/object-visitor.hh.
 */

#pragma once

#include <ast/all.hh>
#include <ast/object-visitor.hh>
#include <misc/contract.hh>

namespace ast
{
  template <template <typename> class Const>
  GenObjectVisitor<Const>::GenObjectVisitor()
    : GenVisitor<Const>()
  {}

  template <template <typename> class Const>
  GenObjectVisitor<Const>::~GenObjectVisitor()
  {}

  /*-------------------------------.
  | Object-related visit methods.  |
  `-------------------------------*/

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<ClassTy>& e)
  {
    // FIXME: Some code was deleted here.
    e.super_get().accept(*this);
    for (const auto dec : e.chunks_get())
        dec->accept(*this);

  }

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<MethodChunk>& e)
  {
    // FIXME: Some code was deleted here.
    for (const auto dec : e)
          dec->accept(*this);

  }

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<MethodDec>& e)
  {
    // FIXME: Some code was deleted here.
    e.formals_get().accept(*this);
    if (e.result_get() != nullptr)
        e.result_get()->accept(*this);
    if (e.body_get() != nullptr)
        e.body_get()->accept(*this);


  }

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<MethodCallExp>& e)
  {
    // FIXME: Some code was deleted here.
    if(e.args_get())
    {

        for (auto& v : *e.args_get())
        {
            v->accept(*this);
        }
    }
    e.object_get()->accept(*this);
  }

  template <template <typename> class Const>
  void GenObjectVisitor<Const>::operator()(const_t<ObjectExp>& e)
  {
    // FIXME: Some code was deleted here.
    e.type_name_get()->accept(*this);

  }

} // namespace ast
