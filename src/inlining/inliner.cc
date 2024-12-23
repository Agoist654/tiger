/**
 ** \file inlining/inliner.cc
 ** \brief Implementation of inlining::Inliner.
 */

#include <boost/graph/transitive_closure.hpp>

#include <ranges>
#include <callgraph/libcallgraph.hh>
#include <inlining/inliner.hh>
#include <parse/libparse.hh>
#include <parse/tweast.hh>

namespace inlining
{
  using namespace ast;

  Inliner::Inliner(const ast::Ast& tree)
    : super_type()
    , rec_funs_()
  {
    // Compute the transitive closure of the call graph to compute the
    // set of recursive functions.
    const callgraph::CallGraph* graph = callgraph::callgraph_compute(tree);
    callgraph::CallGraph closure;
    boost::transitive_closure(*graph, closure);

    // Re-attach properties to the vertices.
    for (auto [i, i_end] = boost::vertices(closure); i != i_end; ++i)
      closure[*i] = (*graph)[*i];
    // Detect recursive functions.
    for (auto [i, i_end] = boost::vertices(closure); i != i_end; ++i)
      {
        for (auto [j, j_end] = boost::adjacent_vertices(*i, closure);
             j != j_end; ++j)
          if (*i == *j)
            rec_funs_.insert(closure[*i]);
      }
    delete graph;
  }

  const misc::set<const ast::FunctionDec*>& Inliner::rec_funs_get() const
  {
    return rec_funs_;
  }

  // FIXME: Some code was deleted here.
   void Inliner::operator()(const ast::CallExp& e)
   {
        if(rec_funs_get().contains(e.def_get()))
            super_type::operator()(e);
        else
        {
            exps_type* args = recurse_collection(*e.args_get());
            auto fun_ref = recurse(*e.def_get());
            parse::Tweast in;
            parse::Tweast in2;

            const Location& location = e.location_get();
            auto k = 0;
            for (auto arg : fun_ref->formals_get().decs_get())
            {
                in << "var " << arg->name_get() << " : " << arg->type_name_get()->name_get() << " := " <<  args->at(k++);
            }

            in << "var res : " << fun_ref->result_get()->name_get() << " := " << recurse(*fun_ref->body_get());

            ChunkList* decs = std::get<ast::ChunkList*>(parse::parse(in));

            in2 << "res";

            Exp* body = std::get<ast::Exp*>(parse::parse(in2));
            result_ = new LetExp(location, decs, body);

        }
   }



} // namespace inlining
