/**
 ** \file desugar/desugar-visitor.cc
 ** \brief Implementation of desugar::DesugarVisitor.
 */

#include <ast/all.hh>
#include <ast/libast.hh>
#include <desugar/desugar-visitor.hh>
#include <misc/algorithm.hh>
#include <misc/symbol.hh>
#include <parse/libparse.hh>
#include <parse/tweast.hh>

namespace desugar
{
  DesugarVisitor::DesugarVisitor(bool desugar_for_p, bool desugar_string_cmp_p)
    : super_type()
    , desugar_for_p_(desugar_for_p)
    , desugar_string_cmp_p_(desugar_string_cmp_p)
  {}

  /*-----------------------------.
  | Desugar string comparisons.  |
  `-----------------------------*/
  void DesugarVisitor::operator()(const ast::OpExp& e)
  {
    // FIXME: Some code was deleted here.
    parse::Tweast in;
    // && e.left_get().type_get()  && e.right_get().type_get() == 
    if(desugar_string_cmp_p_)
    {
      
       switch(e.oper_get())
       {
           case ast::OpExp::Oper::add:
               in << "concat(" << e.left_get() << ", " << e.right_get() << ")";
               break;
           case ast::OpExp::Oper::eq:
               in << "streq(" << e.left_get() << ", " << e.right_get() << ")";
               break;
           case ast::OpExp::Oper::ne:
               in << "streq(" << e.left_get() << ", " << e.right_get() << ") = 0";
               break;
           case ast::OpExp::Oper::lt:
                in << "strcmp(" << e.left_get() << ", " << e.right_get() << ") = -1";
               break;
           case ast::OpExp::Oper::le:
               in << "strcmp(" << e.left_get() << ", " << e.right_get() << ") >= 0";
               break;
           case ast::OpExp::Oper::gt:
               in << "strcmp(" << e.left_get() << ", " << e.right_get() << ") > 1";
               break;
           case ast::OpExp::Oper::ge:
               in << "strcmp(" << e.left_get() << ", " << e.right_get() << ") >= 0";
               break;

       }
       auto res = parse::parse(in);
    }


  }

  /*----------------------.
  | Desugar `for' loops.  |
  `----------------------*/

  /*<<-
    Desugar `for' loops as `while' loops:

       for i := lo to hi do
         body

     is transformed as:

       let
         var _lo := lo
         var _hi := hi
         var i := _lo
       in
         if i <= _hi then
           while 1 do
             (
               body;
               if i = _hi then
                 break;
               i := i + 1
             )
       end

     Notice that:

     - a `_hi' variable is introduced so that `hi' is evaluated only
       once;

     - a `_lo' variable is introduced to prevent `i' from being in the
       scope of `_hi';

     - a first test is performed before entering the loop, so that the
       loop condition becomes `i < _hi' (instead of `i <= _hi'); this
       is done to prevent overflows on INT_MAX.
       ->>*/

  void DesugarVisitor::operator()(const ast::ForExp& e)
  {
    parse::Tweast in;
    misc::symbol local_var = e.vardec_get().name_get();
    if(desugar_for_p_)
    {
       in << "let\n";
       in << "var _lo := " << *e.vardec_get().init_get() << "\n";
       in << " var _hi := " << e.hi_get() << "\n";
       in << " var " << local_var << " := _lo" << "\n";
       in << "in\n";
       in << "if " << local_var << " <= " << "_hi then\n";
       in << "while 1 do \n( " << e.body_get() << ";" << "\n";
       in << "if " << local_var << " = _hi then break;" << "\n";
       in << local_var << " := " << local_var << " + 1 )  end";

       auto res = parse::parse(in);
    }

  }

} // namespace desugar
