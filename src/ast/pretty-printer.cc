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

  void PrettyPrinter::operator()(const SimpleVar& e)
  {
    ostr_ << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << e.def_get() << " */ ";
  }

  void PrettyPrinter::operator()(const FieldVar& e)
  {
      // FIXME: Some code was deleted here.
      /*DONE*/
      ostr_ << *e.var_get();
//      if (bindings_display(ostr_))
//          ostr_<< " /* " << &e/*.var_get()*/ << " */";

      ostr_  << "." << e.name_get();
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
      ostr_ << *e.Type_name_get() << "[ " <<  *e.size_get()<< " ] of " <<*e.init_get() ;
  }

  void PrettyPrinter::operator()(const ArrayTy& e)
  {
      ostr_ << "array of " << e.base_type_get();
  }

  void PrettyPrinter::operator()(const AssignExp& e)
  {
      ostr_ << *e.var_get() << " := " << *e.exp_get();
  }

  void PrettyPrinter::operator()(const BreakExp& e)
  {
      (void)e;
      ostr_ << "break";

      if (bindings_display(ostr_))
        ostr_<< " /* " << e.def_get() << " */ ";
  }

  void PrettyPrinter::operator()(const CallExp& e)
  {
      ostr_ << e.name_get();

      if (bindings_display(ostr_))
        ostr_<< " /* " << e.def_get() << " */";
      ostr_ << "(";
      if (e.args_get() != nullptr)
          ostr_ << misc::separate(*e.args_get(), ",");
      ostr_ << ")";
  }

  void PrettyPrinter::operator()(const Field& e)
  {
      ostr_ << e.name_get();
     // if (bindings_display(ostr_))
        //ostr_<< " /* " << &e << " */";
      ostr_ << " : " << e.type_name_get();
      //if (bindings_display(ostr_))
        //ostr_<< " /* " << &e << " */";
  }

  void PrettyPrinter::operator()(const FieldInit& e)
  {
      ostr_ << e.name_get() << " = " << e.init_get() << " ";
  }

  void PrettyPrinter::operator()(const ForExp& e)
  {
      ostr_ << "for ";
      if (bindings_display(ostr_))
        ostr_<< " /* " << &e << " */ ";
      ostr_ << e.vardec_get().name_get() << " := ";
      if (e.vardec_get().init_get() != nullptr)
          ostr_ << *e.vardec_get().init_get() << " to ";
          ostr_ << e.hi_get() << " do";
          ostr_ << misc::incendl << e.body_get() << misc::incendl;
  }

  void PrettyPrinter::operator()(const FunctionDec& e)
  {

      if (e.body_get() != nullptr)
      {
          ostr_ << "function " << e.name_get();
          if (bindings_display(ostr_))
              ostr_<< " /* " << &e << " */";
          ostr_ << "(" << misc::separate(e.formals_get(), ",") << ")";
      }
      else
      {
          ostr_ << "primitive " << e.name_get();
          if (bindings_display(ostr_))
              ostr_<< " /* " << &e << " */ ";
          ostr_ << "(" << misc::separate(e.formals_get(), ",") << ")";
      }


      if (e.result_get() != nullptr)
          ostr_ << " : " << *e.result_get() ;
      if (e.body_get() != nullptr)
          ostr_ << " =" << misc::incendl << *e.body_get() << misc::incendl;
      else
          ostr_ << misc::iendl;

  }
  void PrettyPrinter::operator()(const IfExp& e)
  {
      ostr_ << "if (" << *e.test_get() << ") then" << misc::incendl <<*e.thenclause_get() << misc::decendl;
      if (e.elseclause_get() != nullptr)
      {
          ostr_ << "else" << misc::incendl << *e.elseclause_get();
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
          ostr_ << *e.decs_get();
      ostr_ << misc::iendl << "in";
      if (e.body_get() != nullptr)
          ostr_  << misc::incendl << *e.body_get();
      ostr_ << misc::iendl << "end";
  }

  void PrettyPrinter::operator()(const NameTy& e)
  {
      ostr_ << e.name_get();

      if (bindings_display(ostr_))
        ostr_<< " /* " << e.def_get() << " */ ";

//      if (e.def_get() != nullptr)
//      {
//          ostr_ << " := " << e.def_get();
//          if (bindings_display(ostr_))
//              ostr_<< " /* " << &e/*.def_get()*/ << " */ ";
//      }
  }

  void PrettyPrinter::operator()(const NilExp& e)
  {
      (void)e;
      ostr_ << "nil";
  }

  void PrettyPrinter::operator()(const OpExp& e)
  {
      ostr_ << "(" << e.left_get() << ") " << str(e.oper_get()) << " " << "(" << e.right_get() << ")";
  }

  void PrettyPrinter::operator()(const RecordExp& e)
  {
      ostr_ << *e.type_name_get() <<  " { ";
      if (!e.fields_get()->empty())
          ostr_ << misc::separate(*e.fields_get(), ",");
      ostr_ << " } ";
  }

  void PrettyPrinter::operator()(const RecordTy& e)
  {
      ostr_ << "{";
      if (!e.fields_get()->empty())
          ostr_ << misc::separate(*e.fields_get(), ",");
      ostr_ << "}";
  }

  void PrettyPrinter::operator()(const SeqExp& e)
  {
      if (!e.exps_get().empty())
      {
          if (e.exps_get().size() != 1)
          ostr_ << "(" << misc::incendl << misc::separate(e.exps_get(), ";\n    ") << misc::resetindent << misc::incendl <<")";
          else
              ostr_ << misc::separate(e.exps_get(), ";\n");
      }
      else
          ostr_ << misc::resetindent  << misc::incindent << misc::incendl << "()";
  }

  void PrettyPrinter::operator()(const StringExp& e)
  {
      ostr_ << "\"" << misc::escape(e.value_get()) << "\"";
  }

  void PrettyPrinter::operator()(const TypeDec& e)
  {
      ostr_ << "type " << e.name_get() ;
      if (bindings_display(ostr_))
          ostr_<< " /* " << &e << " */ ";
         ostr_ << " = " << e.ty_get() << misc::iendl;
  }

  void PrettyPrinter::operator()(const VarDec& e)
  {
      if (e.init_get() != nullptr)
          ostr_<< "var ";
      ostr_ << e.name_get();
      if (bindings_display(ostr_))
        ostr_<< " /* " << &e/*.name_get()*/ << " */ ";

      if (e.type_name_get() != nullptr)
          ostr_ << " : " << *e.type_name_get();
      if (e.init_get() != nullptr)
          ostr_<< " := " << *e.init_get() << misc::iendl;
  }

  void PrettyPrinter::operator()(const WhileExp& e)
  {
      ostr_ << "while ";
      if (bindings_display(ostr_))
        ostr_<< " /* " << &e << " */ ";
      ostr_ << e.test_get() << " do" << misc::incendl << e.body_get() << misc::decendl;
  }

} // namespace ast
