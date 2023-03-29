/**
 ** \file ast/pretty-printer.cc
 ** \brief Implementation of ast::PrettyPrinter.
 */

#include <ast/all.hh>
#include <ast/libast.hh>
#include <ast/pretty-printer.hh>
#include <misc/escape.hh>
#include <misc/indent.hh>
#include <misc/separator.hh>

namespace ast
{
  // Anonymous namespace: these functions are private to this file.
  namespace
  {

    /// \brief Output \a e on \a ostr.
    ///
    /// Used to factor the output of the name declared,
    /// and its possible additional attributes.
    inline std::ostream& operator<<(std::ostream& ostr, const Dec& e)
    {
      ostr << e.name_get();
      return ostr;
    }
  } // namespace

  PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : ostr_(ostr)
  {}

  void PrettyPrinter::operator()(const SimpleVar& e) { ostr_ << e.name_get(); }

  void PrettyPrinter::operator()(const FieldVar& e)
  {
    // FIXME: Some code was deleted here.
    /*DONE*/
    ostr_ << e.var_get() << "." << e.name_get();
  }

  /* Foo[10]. */
  void PrettyPrinter::operator()(const SubscriptVar& e)
  {
    ostr_ << e.var_get() << '[' << misc::incindent << e.index_get()
          << misc::decindent << ']';
  }

  void PrettyPrinter::operator()(const CastExp& e)
  {
    ostr_ << "_cast(" << e.exp_get() << ", " << e.ty_get() << ')';
  }

  // FIXME: Some code was deleted here.
  /*DONE*/
  void PrettyPrinter::operator()(const ArrayExp& e)
  {
      ostr_ << "ID" << "[ " << e.init_get() << " ] of " << e.Type_name_get();
  }

  void PrettyPrinter::operator()(const ArrayTy& e)
  {
      ostr_ << "array of " << e.base_type_get();
  }

  void PrettyPrinter::operator()(const AssignExp& e)
  {
      ostr_ << e.var_get() << " := " << e.exp_get();
  }

  void PrettyPrinter::operator()(const BreakExp& e)
  {
      (void)e;
      ostr_ << "break";
  }

  void PrettyPrinter::operator()(const CallExp& e)
  {
      ostr_ << e.name_get() << "(" << misc::separate(*e.args_get(), ",") << ")";
  }

  void PrettyPrinter::operator()(const Field& e)
  {
      ostr_ << e.name_get() << " : " << e.type_name_get();
  }

  void PrettyPrinter::operator()(const FieldInit& e)
  {
      ostr_ << e.name_get() << " := " << e.init_get();
  }

  void PrettyPrinter::operator()(const ForExp& e)
  {
      ostr_ << "for " << e.vardec_get().name_get() << " := " << e.vardec_get().init_get() << " to " << e.hi_get() << " do" << misc::incendl << e.body_get() << misc::decendl;
  }

  void PrettyPrinter::operator()(const FunctionDec& e)
  {
          ostr_ << "function " << e.name_get() << "(" << e.formals_get() << ")" ;
      if (e.result_get() != nullptr)
          ostr_ << " : " << e.result_get() ;
      if (e.body_get() != nullptr)
          ostr_ << " =" << misc::incendl << *e.body_get() << misc::decendl;
      else
          ostr_ << misc::iendl;
  }
  void PrettyPrinter::operator()(const IfExp& e)
  {
      ostr_ << "if " << e.test_get() << " then" << misc::incendl << e.thenclause_get() << misc::decendl;
      if (e.elseclause_get() != nullptr)
      {
          ostr_ << "else" << misc::incendl << e.elseclause_get() << misc::decendl;
      }
  }

  void PrettyPrinter::operator()(const IntExp& e)
  {
      ostr_ << e.value_get();
  }

  void PrettyPrinter::operator()(const LetExp& e)
  {
      ostr_ << "let" << misc::incendl;
      if (e.decs_get() != nullptr)
          ostr_ <<*e.body_get()/* *e.decs_get() */<< misc::decendl << "in" << misc::incendl;
      if (e.body_get() != nullptr)
          ostr_ << *e.body_get();
      ostr_ << misc::decendl << "end";
  }

  void PrettyPrinter::operator()(const NameTy& e)
  {
      ostr_ << e.name_get();
      if (e.def_get() != nullptr)
      {
          ostr_ << " = " << e.def_get();
      }
  }

  void PrettyPrinter::operator()(const NilExp& e)
  {
      (void)e;
      ostr_ << "nil";
  }

  void PrettyPrinter::operator()(const OpExp& e)
  {
      ostr_ << e.left_get() << " " << str(e.oper_get()) << " " << e.right_get();
  }

  void PrettyPrinter::operator()(const RecordExp& e)
  {
      ostr_ << e.type_name_get() <<  " " << e.fields_get() << " = ";
  }

  void PrettyPrinter::operator()(const RecordTy& e)
  {
      ostr_ << "{" << e.fields_get() << "}";
  }

  void PrettyPrinter::operator()(const SeqExp& e)
  {
      if (!e.exps_get().empty())
          ostr_ << "(" << misc::incendl << misc::separate(e.exps_get(), ";") << misc::resetindent << misc::incendl <<")";
      else
          ostr_ << misc::resetindent  << misc::incindent << misc::incendl << "()";
  }

  void PrettyPrinter::operator()(const StringExp& e)
  {
      ostr_ << "\"" << misc::escape(e.value_get()) << "\"";
  }

  void PrettyPrinter::operator()(const TypeDec& e)
  {
      ostr_ << e.ty_get() << " " << e.name_get();
  }

  void PrettyPrinter::operator()(const VarDec& e)
  {
      ostr_ << "var "<< e.name_get() <<  " : " << e.type_name_get() << " := " << e.init_get();
  }

  void PrettyPrinter::operator()(const WhileExp& e)
  {
      ostr_ << "while " << e.test_get() << " do" << misc::incendl << e.body_get() << misc::decendl;
  }

} // namespace ast
