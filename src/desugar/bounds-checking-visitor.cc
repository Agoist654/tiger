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
        /*:parse::Tweast in;

        in << "let type _box_" << e.int_array = array of int\n" ;
        in << "type _int_array = {\n";
        in << "arr : __int_array,\nsize : int\n}\n";

        in << 

        result_ = std::get<ast::Exp*>(parse::parse(in));*/
      super_type::operator()(e);


  }
  void BoundsCheckingVisitor::operator()(const ast::ArrayExp& e)
  {
      //boxes_[e] = e.size_get()
      parse::Tweast in;

      in << "let var _size := " << e.size_get();
      in << "\n" << "in\n";
      in << "_box_" << e.Type_name_get()->name_get() << " = {\n";
      in << "arr : " << e.Type_name_get()->name_get() << " [_size] of " << e.init_get();
      in <<",\nsize = _size }\nend\n";

      result_ = std::get<ast::Exp*>(parse::parse(in));

  }

  void BoundsCheckingVisitor::operator()(const ast::FunctionDec& e)
  {
      //boxes_[e] = e.size_get();
      super_type::operator()(e);
      if(e.name_get() == "main_")
      {
        //std::cout << "HELLO WORLD\n";

        parse::Tweast in;

        in << "let type __int_array = array of int\n" ;
        in << "type _int_array = {\n";
        in << "arr : __int_array,\nsize : int\n}\n";


        result_ = std::get<ast::Exp*>(parse::parse(in));

      }
  }


} // namespace desugar
