/**
 ** \file overload/type-checker.hh
 ** \brief Checking/translating an OverTiger program in a Tiger program.
 */

#pragma once

#include <overload/binder.hh>
#include <type/type-checker.hh>
#include <type/types.hh>

namespace overload
{
  /** \brief Perform type checking, allowing function overload, and compute
   ** the bindings of the functions.
   **
   ** Inheritance is declared virtual to enable diamond inheritance with
   ** the combine::TypeChecker (src/combine/type-checker.hh), inheriting
   ** from overload::TypeChecker and object::TypeChecker, both inheriting from
   ** type::TypeChecker.
   **/
  class TypeChecker : virtual public type::TypeChecker
  {
  public:
    /// Superclass.
    using super_type = type::TypeChecker;
    using super_type::operator();

    TypeChecker(const overfun_bindings_type& overfun_bindings);
    virtual ~TypeChecker() = default;

    // FIXME: Some code was deleted here.
    void operator()(ast::CallExp& e) override;
    const overfun_bindings_type& overfun_bindings_get();
    bool  check_types(const ast::Ast& ast,
                                const std::string& exp1,
                                const type::Type& type1,
                                const std::string& exp2,
                                const type::Type& type2);
      bool      check_types(const ast::Ast& ast,
                                const std::string& exp1,
                                ast::Typable& type1,
                                const std::string& exp2,
                                ast::Typable& type2);

    
//template <class D> void chunk_visit(ast::Chunk<D>& e)


  private:
    const overfun_bindings_type& overfun_bindings_;
  };

} // namespace overload
