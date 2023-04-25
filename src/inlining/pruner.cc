/**
 ** \file inlining/pruner.cc
 ** \brief Implementation of inlining::Pruner.
 */

#include <inlining/pruner.hh>

namespace inlining
{
  using namespace ast;

  ast::FunctionChunk* Pruner::prune(ast::FunctionChunk& e)
  {
    while (true)
      {
        auto [remove_begin, remove_end] =
          std::ranges::remove_if(e, [&](ast::FunctionDec* func_dec) {
            if (!func_dec->body_get() || func_dec->name_get() == "_main")
              return false;
            else
              return called_functions_[func_dec->name_get()] == 0;
          });

        if (remove_begin == remove_end)
          break;
        e.erase(remove_begin, remove_end);
      }

    return new FunctionChunk(e.location_get(), &e.decs_get());
  }

  // FIXME: Some code was deleted here.
  void Pruner::operator()(const ast::FunctionDec& e)
  {
        current_function_ =  &e; //useless line ?
        //operator()(e.body_get);
        super_type::operator()(e);
  }

  void Pruner::operator()(const ast::CallExp& e)
  {
      called_functions_[e.name_get()]++;
      super_type::operator()(e);
  }

  void Pruner::operator()(const ast::LetExp& e)
  {
        //operator()(e.decs_get());
        operator()(e.body_get());

        const Location& location = e.location_get();
        ChunkList* decs = recurse(*e.decs_get());
        Exp* body = recurse(*e.body_get());
        result_ = new LetExp(location, decs, body);
  }

  void Pruner::operator()(const ast::FunctionChunk& e)
  {
     super_type::operator()(e);
     //result_ = prune(dynamic_cast<ast::Chunk<ast::FunctionDec>*>(result_));
  }


} // namespace inlining
