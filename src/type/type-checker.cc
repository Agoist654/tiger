/**
 ** \file type/type-checker.cc
 ** \brief Implementation for type/type-checker.hh.
 */

#include <memory>
#include <ranges>

#include <ast/all.hh>
#include <type/type-checker.hh>
#include <type/types.hh>

namespace type
{
  TypeChecker::TypeChecker()
    : super_type()
    , error_()
  {}

  const Type* TypeChecker::type(ast::Typable& e)
  {
    // FIXME: Some code was deleted here.
    if (e.type_get() == nullptr)
          e.accept(*this);
      //super_type::operator()(e);
      return e.type_get();
  }

  const Record* TypeChecker::type(const ast::fields_type& e)
  {
    auto res = new Record;
    // FIXME: Some code was deleted here.
    return res;
  }

  const Record* TypeChecker::type(const ast::VarChunk& e)
  {
    auto res = new Record;
    for (const auto& var : e)
      res->field_add(var->name_get(), *type(*var));

    return res;
  }

  const misc::error& TypeChecker::error_get() const { return error_; }

  /*-----------------.
  | Error handling.  |
  `-----------------*/

  void TypeChecker::error(const ast::Ast& ast, const std::string& msg)
  {
    error_ << misc::error::error_type::type << ast.location_get() << ": " << msg
           << std::endl;
  }

  void TypeChecker::type_mismatch(const ast::Ast& ast,
                                  const std::string& exp1,
                                  const Type& type1,
                                  const std::string& exp2,
                                  const Type& type2)
  {
    error_ << misc::error::error_type::type << ast.location_get()
           << ": type mismatch" << misc::incendl << exp1 << " type: " << type1
           << misc::iendl << exp2 << " type: " << type2 << misc::decendl;
  }

  void TypeChecker::check_types(const ast::Ast& ast,
                                const std::string& exp1,
                                const Type& type1,
                                const std::string& exp2,
                                const Type& type2)
  {
    // FIXME: Some code was deleted here (Check for type mismatch).

  if (!type1.compatible_with(type2))
  {
    error_ << misc::error::error_type::type << ast.location_get()
           << ": check type " << misc::incendl << exp1 << " type: " << type1
           << misc::iendl << exp2 << " type: " << type2 << misc::decendl;
               //("expected type: " << type2 << "got: " << type1)
  }

    // If any of the type is Nil, set its `record_type_` to the other type.
    if (!error_)
      {
        // FIXME: Some code was deleted here.
      }
  }

  void TypeChecker::check_types(const ast::Ast& ast,
                                const std::string& exp1,
                                ast::Typable& type1,
                                const std::string& exp2,
                                ast::Typable& type2)
  {
    // Ensure evaluation order.
    type(type1);
    type(type2);
    // FIXME: Some code was deleted here (Check types).

    check_types(ast, exp1, *type1.type_get(), exp2, *type2.type_get());
  }

  /*--------------------------.
  | The core of the visitor.  |
  `--------------------------*/

  /*-----------------.
  | Visiting /Var/.  |
  `-----------------*/

  void TypeChecker::operator()(ast::SimpleVar& e)
  {
    // FIXME: Some code was deleted here.
    e.type_set(&e.def_get()->type_get()->actual());
  }

  // FIXME: Some code was deleted here.

  /*-----------------.
  | Visiting /Exp/.  |
  `-----------------*/

  // Literals.
  void TypeChecker::operator()(ast::NilExp& e)
  {
    auto nil_ptr = std::make_unique<Nil>();
    type_default(e, nil_ptr.get());
    created_type_default(e, nil_ptr.release());
  }

  void TypeChecker::operator()(ast::IntExp& e)
  {
    // FIXME: Some code was deleted here.
    type_default(e, &Int::instance());
  }

  void TypeChecker::operator()(ast::StringExp& e)
  {
    // FIXME: Some code was deleted here.
     type_default(e, &String::instance());
  }

  // Complex values.

  void TypeChecker::operator()(ast::RecordExp& e)
  {
    // FIXME: Some code was deleted here.
  }

  void TypeChecker::operator()(ast::OpExp& e)
  {
    // FIXME: Some code was deleted here.
      e.type_set(&Int::instance());
      type(e.left_get());
      type(e.right_get());

      check_types(e, "left operand type: ", e.left_get(), "right operand type: ", e.right_get());

      if (dynamic_cast<const Int*>(&e.left_get().type_get()->actual()) != nullptr && dynamic_cast<const Int*>(&e.right_get().type_get()->actual()) != nullptr)
      {
          //le && ne sert a r mais whatever
          return;
      }

      if (dynamic_cast<const String*>(&e.left_get().type_get()->actual()) != nullptr && dynamic_cast<const String*>(&e.right_get().type_get()->actual()) != nullptr)
      {
          if (e.oper_get() == ast::OpExp::Oper::eq || e.oper_get() == ast::OpExp::Oper::ne)
          {
              check_type(e.left_get(), "left operand is a string can't be op with artimetiaue op", *e.type_get());
              check_type(e.right_get(), "right opreand is a string can't be op with artimetiaue op", *e.type_get());
          }
      }

/*
      if (e.oper_get() == ast::OpExp::Oper::add || e.oper_get() == ast::OpExp::Oper::sub || e.oper_get() == ast::OpExp::Oper::mul || e.oper_get() == ast::OpExp::Oper::div)
      {
          check_type(e.left_get(), "op arthm with left operand not a int", &Int::instance());
          check_type(e.right_get(), "op arthm with right operand not a int", &Int::instance());
      }
*/
  }

  // FIXME: Some code was deleted here.

  /*-----------------.
  | Visiting /Dec/.  |
  `-----------------*/

  /*------------------------.
  | Visiting FunctionChunk. |
  `------------------------*/

  void TypeChecker::operator()(ast::FunctionChunk& e)
  {
    chunk_visit<ast::FunctionDec>(e);
  }

  void TypeChecker::operator()(ast::FunctionDec&)
  {
    // We must not be here.
    unreachable();
  }

  // Store the type of this function.
  template <>
  void TypeChecker::visit_dec_header<ast::FunctionDec>(ast::FunctionDec& e)
  {
    // FIXME: Some code was deleted here.

          e.formals_get().accept(*this);
          if(e.result_get())
            e.result_get()->accept(*this);
          else
          {
              e.type_set(&Void::instance());
          }
  }

  // Type check this function's body.
  template <>
  void TypeChecker::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e)
  {
    if (e.body_get())
      visit_routine_body<Function>(e);
  }

  /*---------------.
  | Visit VarDec.  |
  `---------------*/

  void TypeChecker::operator()(ast::VarDec& e)
  {
//      // FIXME: Some code was deleted here.
//      if (e.init_get() != nullptr)
//          type(*e.init_get());
//
//      if (e.type_name_get() != nullptr)
//      {
//          type(*e.type_name_get());
//          check_types(e, "vardec expected type: ", *e.type_name_get()/*->type_get()*/, "got: ", *e.init_get()/*->type_get()*/);
//      }
//
//      else
//          e.type_set(e.init_get()->type_get());

      if (e.init_get() != nullptr)
      {
          auto t = type(*e.init_get());
          type_default(e, t);
      }

      if (e.type_name_get() != nullptr)
      {
          type(*e.type_name_get());
          if (e.init_get() != nullptr)
                check_types(e, "type should be: ", *e.type_name_get(), "got: ", *e.init_get());
      }

  }

  /*--------------------.
  | Visiting TypeChunk. |
  `--------------------*/

  void TypeChecker::operator()(ast::TypeChunk& e)
  {
    chunk_visit<ast::TypeDec>(e);
  }

  void TypeChecker::operator()(ast::TypeDec&)
  {
    // We must not be here.
    unreachable();
  }

  // Store this type.
  template <> void TypeChecker::visit_dec_header<ast::TypeDec>(ast::TypeDec& e)
  {
    // We only process the head of the type declaration, to set its
    // name in E.  A declaration has no type in itself; here we store
    // the type declared by E.
    // FIXME: Some code was deleted here.

      auto named = new Named(e.name_get());
      created_type_default(e, named);
      type_default(e, named);

  }

  // Bind the type body to its name.
  template <> void TypeChecker::visit_dec_body<ast::TypeDec>(ast::TypeDec& e)
  {
    // FIXME: Some code was deleted here.

      auto new_type = type(e.ty_get());

      auto named = dynamic_cast<const Named*>(e.type_get());
      //check_type(e.ty_get(), "wrong c of type: ", *named);
      named->type_set(new_type);
  }

  /*------------------.
  | Visiting /Chunk/. |
  `------------------*/

  template <class D> void TypeChecker::chunk_visit(ast::Chunk<D>& e)
  {
    // FIXME: Some code was deleted here.

    // Shorthand.
    using chunk_type = ast::Chunk<D>;
    // FIXME: Some code was deleted here (Two passes: once on headers, then on bodies).
    //std::map<misc::symbol, D*> m;

    for (auto& dec : e.decs_get())
    {
        /*if (m.contains(dec->name_get()))
        {
            //check_main(e);
            redefinition(*m.find(dec->name_get())->second, *dec);
            return;
        }*/
        //m[dec->name_get()] = dec;
        visit_dec_header(*dec);
        //visit_dec_body(*dec);
    }

    for (auto& dec : e.decs_get())
    {
        visit_dec_body(*dec);
    }
  }


  /*-------------.
  | Visit /Ty/.  |
  `-------------*/

  void TypeChecker::operator()(ast::NameTy& e)
  {
    // FIXME: Some code was deleted here (Recognize user defined types, and built-in types).

      if (e.def_get() != nullptr)
          e.type_set(e.def_get()->type_constructor_get());

      else if (e.name_get().get() == "int")
          type_default(e, &Int::instance());

      else//string
          type_default(e, &String::instance());

  }

  void TypeChecker::operator()(ast::RecordTy& e)
  {
    // FIXME: Some code was deleted here.
  }

  void TypeChecker::operator()(ast::ArrayTy& e)
  {
    // FIXME: Some code was deleted here.
  }


  // MY_FIXME: Exp
  void TypeChecker::operator()(ast::SeqExp& e)
  {

      if (e.exps_get().empty())
          e.type_set(&Void::instance());
      else
      {
          for (auto exp : e.exps_get())
          {
              type(*exp);
              e.type_set(exp->type_get());
          }
      }
    }

  void TypeChecker::operator()(ast::IfExp& e)
  {

      //check_types de test -> int

      if (e.elseclause_get() == nullptr)
          e.elseclause_get()->type_set(&Void::instance());

      check_types(e, "then type: ", *e.test_get(), "else type: ", *e.elseclause_get());
  }


} // namespace type
