/**
 ** \file desugar/bounds-checking-visitor.cc
 ** \brief Implementation of desugar::BoundsCheckingVisitor.
 */

#include <ast/all.hh>
#include <ast/libast.hh>
#include <desugar/bounds-checking-visitor.hh>
#include <misc/symbol.hh>
#include <parse/libparse.hh>

namespace desugar
{
  namespace
  {
    /// Return the name of the boxed type for \a s.
    std::string box(misc::symbol s) { return "_box_" + s.get(); }

  } // namespace

  BoundsCheckingVisitor::BoundsCheckingVisitor()
    : super_type()
  {}

  /*-----------------------.
  | Array bounds checking.  |
  `-----------------------*/

  // FIXME: Some code was deleted here.
  void BoundsCheckingVisitor::operator()(const ast::ArrayTy& e)
  {
        parse::Tweast in;

        in << "let type __int_array = array of int\n" ;
        in << "type _int_array = {\n";
        in << "arr : __int_array,\nsize : int\n}";

        result_ = std::get<ast::Exp*>(parse::parse(in));


  }
  void BoundsCheckingVisitor::operator()(const ast::ArrayExp& e)
  {
      //boxes_[e] = e.size_get();
      super_type::operator()(e);
  }

} // namespace desugar
