/**
 ** \file ast/type-dec.hh
 ** \brief Declaration of ast::TypeDec.
 */

#pragma once

#include <ast/dec.hh>
#include <ast/ty.hh>
#include <ast/type-constructor.hh>

namespace ast
{
  /// TypeDec.
  class TypeDec
    : public Dec
    , public TypeConstructor
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a TypeDec node.
    TypeDec(const Location& location, misc::symbol name, Ty* ty);
    TypeDec(const TypeDec&) = delete;
    TypeDec& operator=(const TypeDec&) = delete;
    /// Destroy a TypeDec node.
    ~TypeDec() override;
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
     ** \{ */
    /// Return type definition.
    const Ty& ty_get() const;
    /// Return type definition.
    Ty& ty_get();
    /** \} */

    /// Return definition site.
    TypeDec* def_get() ;
    const TypeDec* def_get() const ;
    /// Set definition site.
    void def_set(TypeDec*);
    /** \} */


  protected:
    /// Type definition.
    Ty* ty_;

    TypeDec* def_ = nullptr;
  };
} // namespace ast
#include <ast/type-dec.hxx>
