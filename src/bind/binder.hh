/**
 ** \file bind/binder.hh
 ** \brief Declaration of bind::Binder.
 **/

#pragma once


#include <ast/default-visitor.hh>
#include <ast/object-visitor.hh>

#include <misc/error.hh>
#include <misc/fwd.hh>
#include <misc/scoped-map.hh>

namespace bind
{
  /** \brief Binding identifier uses to their definitions.
   **
   ** When the \c Binder finds a declaration (of a variable/formal, function,
   ** or type), it keeps a pointer to it.  When it finds a use, it binds it
   ** to its definition, i.e., it annotates it with a pointer to the
   ** declaration.
   **
   ** The \c Binder diagnoses identifier use errors (invalid multiple
   ** definitions, unbound identifiers etc.).
   **
   ** Since identifier bindings depend on scopes, it needs an environment.
   **
   ** In the original Tiger by A. Appel, there are two namespaces: on
   ** the one hand types, and on the other hand functions and variables.
   ** Here, at EPITA, we will use three name spaces: we will allow
   ** variables and functions with the same name.
   **
   ** Moreover, object constructs make use of two additional name
   ** spaces: one for class attributes and one for methods (actually
   ** these two name spaces only live within the scope of a class).
   **
   ** \c Env models this full environment, i.e., the collection of three
   ** tables of symbols: one for functions, one for types, and one for
   ** variables.  The `scope_begin()', `scope_end()', `*get_()' and
   ** `*put_()' are then just handy wrappers around accesses to the
   ** tables of symbols.
   **
   ** Note that this Binder is mainly doing nothing: it is just
   ** interested in declarations and uses.  To avoid writing
   ** all the methods that `do nothing but walk', it derives
   ** from \c ast::DefaultVisitor.
   **/

   // FIXME/*DONE: Some code was deleted here.
  class Binder
    : public ast::DefaultVisitor
    , public ast::ObjectVisitor
  {
  public:
    /// Super class type.
    using super_type = ast::DefaultVisitor;
    /// Import all the overloaded \c operator() methods.
    using super_type::operator();

    /// The error handler.
    const misc::error& error_get() const;

    /* The visiting methods. */
    void operator()(ast::LetExp& e) override;
    /*process*/
    void operator()(ast::Ast& e) override;
    void operator()(ast::BreakExp& e) override;
    void operator()(ast::CallExp& e) override;
    void operator()(ast::VarChunk& e) override;
    void operator()(ast::VarDec& e) override;
    void operator()(ast::TypeChunk& e) override;
    void operator()(ast::FunctionChunk& e) override;
    void operator()(ast::ForExp& e) override;
    void operator()(ast::NameTy& e) override;
    void operator()(ast::SimpleVar& e) override;
    void operator()(ast::WhileExp& e) override;
    void operator()(ast::IfExp& e) override;
    void operator()(ast::TypeDec& e) override;
    void operator()(ast::ChunkList & e) override;




       // ---------------- //
    // Visiting /Dec/.  //
    // ---------------- //

    /// \name Type and Function declarations
    /// \{

    /// When traversing a function (or a type) we both have to bind
    /// its body (i.e., we need to enter a new scope and push the
    /// arguments in it), *and* we have to store the function's
    /// declaration in the current scope (so that other functions can
    /// call it).

    /// We first introduce the function's name in the outer
    /// environment so that the function can call itself recursively.
    /// In the mean time, we also check for uniqueness.  Then, as a
    /// second step, we process the contents of all the functions
    /// belonging to the current chunk.

    /// Therefore there are three methods:
    ///
    /// - \c chunk_visit() performs the double traversal, composed of the
    /// two following functions
    ///
    /// - \c visit_dec_header() visit the declaration to register the
    /// function in the current environment,
    ///
    /// - \c visit_dec_body() visits the body.  Of course for functions it
    /// also inserts the current arguments in the variable table.
    ///
    /// It turns out that \c chunk_visit can be written for both functions
    /// and types, but of course, traversals of headers and bodies
    /// differ.

    /// Check a set of definitions: unique names, browse headers, then
    /// bodies.

    // FIXME/*DONE: Some code was deleted here.
    template <class D> void chunk_visit(ast::Chunk<D>& e);

    /* Check a Function or Type declaration header.*/
    template <class D> void visit_dec_header(D& e);

    /* Check a Function or Type declaration body.*/
    template <class D> void visit_dec_body(D& e);
       /// \}

    /// \name Error handling
    /// \{
  protected:
    /// Report an error.
    void error(const ast::Ast& loc, const std::string& msg);

    /// Check _main definition.
    void check_main(const ast::FunctionDec& e);

    /// Report an undefined symbol.
    ///
    /// \param k   the kind of this node (function, variable, type)
    /// \param e   the node using an undefined name
    template <typename T> void undeclared(const std::string& k, const T& e);
    void undeclared(const std::string& k, const ast::CallExp& e);
    void undeclared(const std::string& k, const ast::NameTy& e);
    void undeclared(const std::string& k, const ast::SimpleVar& e);

    /// Report a symbol redefinition.
    ///
    /// \param e1   the first occurrence, the original
    /// \param e2   the invalid duplicate
    template <typename T> void redefinition(const T& e1, const T& e2);
    /// \}

    /** \name Handling the environment
     ** \{ */
    /// Open a new var, fun, and type scope.

    virtual void scope_begin();
    /// Close the latest var, fun, and type scope.
    virtual void scope_end();
    /** \} */

    /// Binding errors handler.
    misc::error error_;
    misc::scoped_map<misc::symbol, ast::VarDec*> varscope_;
    misc::scoped_map<misc::symbol, ast::FunctionDec*> funscope_;
    misc::scoped_map<misc::symbol, ast::TypeDec*> typescope_;

    std::vector<ast::Exp*> forvector_;

    int nb_main = 0;
    // FIXME/*DONE: Some code was deleted here (More members).
  };

} // namespace bind

#include <bind/binder.hxx>
