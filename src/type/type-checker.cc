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

      type(e.left_get());
      type(e.right_get());
      check_types(e, "left operand type: ", e.left_get(), "right operand type: ", e.right_get());
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
    // FIXME: Some code was deleted here.
      if (e.init_get() != nullptr)
          type(*e.init_get());

      if (e.type_name_get()->type_get() != nullptr)
      {
          type(*e.type_name_get());
          check_types(e, "vardec expected type: ", *e.type_name_get()->type_get(), "got: ", *e.init_get()->type_get());
      }

      else
          e.type_set(e.init_get()->type_get());
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
  }

  // Bind the type body to its name.
  template <> void TypeChecker::visit_dec_body<ast::TypeDec>(ast::TypeDec& e)
  {
    // FIXME: Some code was deleted here.

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


} // namespace type
