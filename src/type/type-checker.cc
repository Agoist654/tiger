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
        if(dynamic_cast<const Nil*>(&type1) != nullptr)
            dynamic_cast<const Nil*>(&type1)->record_type_set(type2);
        else if(dynamic_cast<const Nil*>(&type2) != nullptr)
            dynamic_cast<const Nil*>(&type2)->record_type_set(type1);

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
    e.type_set(e.def_get()->type_get());
  }

  void TypeChecker::operator()(ast::FieldVar& e)
  {
    // FIXME: Some code was deleted here.
      super_type::operator()(e);
      if(dynamic_cast<const Record*>(&e.var_get()->type_get()->actual()) == nullptr)
          error(e, "field's var type is not a record");
      else
      {

          auto type = dynamic_cast<const Record*>(&e.var_get()->type_get()->actual())->field_type(e.name_get());
          if(type == nullptr)
              error(e, "tried to access to an inexistant field");
          e.type_set(type);
      }
  }

  void TypeChecker::operator()(ast::SubscriptVar& e)
  {
      type(e.var_get());
      type(e.index_get());

      auto& t = e.var_get().type_get()->actual();

      if (dynamic_cast<const type::Array*>(&t) == nullptr)
      {
          error(e, "subscriptvar's var's type is not an array");
      }

      check_type(e.index_get(), "index in array must integer", *&Int::instance());

      type_default(e, dynamic_cast<const Array*>(&e.var_get().type_get()->actual())->arrtype_get());
      //std::cout << "\nsubscript "<< &e.var_get().type_get()->actual();
      //std::cout << "\n" << dynamic_cast<const Array*>(&e.var_get().type_get()->actual())->arrtype_get();
      //std::cout << "\n" << e.type_get() << " " << e.type_get()->actual() ;

      //std::cout << dynamic_cast<const Array*>(&e.var_get().type_get()->actual());
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
        type(*e.type_name_get());
        super_type::operator()(e.type_name_get());

        if (dynamic_cast<ast::RecordTy*>(&e.type_name_get()->def_get()->ty_get()) != nullptr)
        {
            auto imma_def = dynamic_cast<ast::RecordTy*>(&e.type_name_get()->def_get()->ty_get());
            auto k = 0;
            if( e.fields_get()->size() != imma_def->fields_get()->size())
                error(e, "numbers of fields in record insantiation do no match");
            for (auto field_init : *e.fields_get())
            {

                super_type::operator()(field_init);
                if(field_init->name_get() != imma_def->fields_get()->at(k)->name_get())
                {
                    error(e, "mismatch record field's name)");
                }
                check_types(e, "the field " + field_init->name_get().get() +"is type: ", field_init->init_get(), "expected: ", imma_def->fields_get()->at(k++)->type_name_get());
            }

        }

        else
        {
            //je fais un checktype avec un type random pour soulever une erreur
            error(e, "recordexp's namety is not a record");
        }

        type_default(e, e.type_name_get()->type_get());
  }

    void TypeChecker::operator()(ast::ArrayExp& e)
    {

        type(*e.Type_name_get());
        super_type::operator()(e.Type_name_get());
        type(*e.size_get());
        type(*e.init_get());

        check_type(*e.size_get(), "array size is not a integer ", *&Int::instance());


        if (dynamic_cast<ast::ArrayTy*>(&e.Type_name_get()->def_get()->ty_get()) != nullptr)
        {
            auto imma_def = dynamic_cast<ast::ArrayTy*>(&e.Type_name_get()->def_get()->ty_get());
            check_types(e, "type inside the array expected: ", imma_def->base_type_get(), "got: ", *e.init_get());
        }

        else
        {
            //je fais un checktype avec un type random pour soulever une erreur
            //std::cout << "HELLO WORLD\n";
            check_type(*e.Type_name_get(), "arrayexp's namety is not a array", *&Void::instance());
        }

        type_default(e, e.Type_name_get()->type_get());

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
          if (e.oper_get() == ast::OpExp::Oper::add || e.oper_get() == ast::OpExp::Oper::sub || e.oper_get() == ast::OpExp::Oper::mul || e.oper_get() == ast::OpExp::Oper::div)
          {
              error(e, "cant do arithmetic on string");
          }
      }

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
      {
          type(*e.result_get());
          type_default(e, e.result_get()->type_get());
      }

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
          {
              visit_routine_body<Function>(e);

              if (e.name_get() == "_main")
              {
                  check_type(*e.body_get(), "main's type must be void", *&Void::instance());
              }
          }
      }

  /*---------------.
  | Visit VarDec.  |
  `---------------*/

  void TypeChecker::operator()(ast::VarDec& e)
  {
      if (e.init_get() != nullptr)
      {
          auto t = type(*e.init_get());
          type_default(e, t);
      }

      if (e.type_name_get() != nullptr)
      {
          auto t = type(*e.type_name_get());
          if (e.init_get() != nullptr)
                check_types(e, "type should be: ", *e.type_name_get(), "got: ", *e.init_get());
          type_set(e, t);
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
      //if (!named->sound())
      //    error(e, "named is not sound");

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
        {
          type_default(e, &Int::instance());
          //std::cout << "\n<INT>\n";
        }

      else//string
          type_default(e, &String::instance());

  }

  void TypeChecker::operator()(ast::RecordTy& e)
  {
    // FIXME: Some code was deleted here.
    auto record = new Record();
    created_type_default(e, record);
    type_default(e, record);
    for (auto field : *e.fields_get())
    {
        super_type::operator()(field);
        record->field_add(field->name_get(), *field->type_name_get().type_get());
    }

    e.type_set(record);

  }

  void TypeChecker::operator()(ast::ArrayTy& e)
  {
    // FIXME: Some code was deleted here.
     // operator()(e.base_type_get());
      type(e.base_type_get());

      auto array = new Array();
      created_type_default(e, array);
      type_default(e, array);
      //e.type_set(array);
      array->arrtype_set(*e.base_type_get().type_get());
      //e.type_set(array);
      //std::cout << "arrayTy " << e.type_get() << "\n";
      //std::cout << "base_type " << e.base_type_get().type_get() << " INT" << &Int::instance() << " array " << array->arrtype_get();
      //super_type::operator()(e.base_type_get());
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

  void TypeChecker::operator()(ast::LetExp& e)
  {
      if (e.decs_get() != nullptr)
      {
          super_type::operator()(*e.decs_get());
      }

      if (e.body_get() == nullptr)
          e.type_set(&Void::instance());
      else
      {
          type(*e.body_get());
          type_default(e, e.body_get()->type_get());
      }
  }

  void TypeChecker::operator()(ast::IfExp& e)
  {

      type(*e.test_get());
      type(*e.thenclause_get());

      check_type(*e.test_get(), "if test should be int", *&Int::instance());

      if (e.elseclause_get() == nullptr)
          check_type(*e.thenclause_get(), "there is no else then thenclause should be void", *&Void::instance());

      else
          check_types(e, "then type: ", *e.thenclause_get(), "else type: ", *e.elseclause_get());
      type_default(e, e.thenclause_get()->type_get());
  }

    void TypeChecker::operator()(ast::CallExp& e)
    {
        auto k = 0;
        if (e.def_get()->formals_get().decs_get().size() != e.args_get()->size())
        {
            error(e, "numbre of arguments missmath");
            return;
        }

        for (auto arg : e.def_get()->formals_get())
        {
            check_types(e, "argument in call exp is not matching the function declaration: ", *arg, "given arg:", *e.args_get()->at(k++));
        }
        type_default(e, e.def_get()->type_get());
    }

    void TypeChecker::operator()(ast::ForExp& e)
    {
        var_read_only_ += &e.vardec_get();

        type_default(e, &Void::instance());

        type(e.vardec_get());
        type(e.hi_get());
        type(e.body_get());

        check_type(e.vardec_get(), "for vardec should: ", *&Int::instance());
        check_type(e.hi_get(), "for hi should: ", *&Int::instance());
        check_type(e.body_get(), "for body should be void", *&Void::instance());
        var_read_only_ -= &e.vardec_get();
    }

    void TypeChecker::operator()(ast::WhileExp& e)
    {
        type_default(e, &Void::instance());

        type(e.test_get());
        type(e.body_get());

        check_type(e.test_get(), "while test should be int", *&Int::instance());
        check_type(e.body_get(), "while body should be void", *&Void::instance());

    }

    void TypeChecker::operator()(ast::BreakExp& e)
    {
        type_default(e, &Void::instance());
    }
    void TypeChecker::operator()(ast::AssignExp& e)
    {
        type(*e.var_get());
        //std::cout << "\nAssign " << e.var_get()->type_get() << "\n";
        type(*e.exp_get());

        if (dynamic_cast<const ast::SimpleVar*>(e.var_get()) != nullptr)
        {
            if (var_read_only_.has(dynamic_cast<const ast::SimpleVar*>(e.var_get())->def_get()))
                error(e, "var in read only in for");
        }

        //type(const_cast<ast::SimpleVar&>(*simplevar));
        //super_type::operator()(*e.exp_get());
        type_default(e, &Void::instance());
        //std::cout << "\nAssign " << e.var_get()->type_get() << "\n";

    }


} // namespace type
