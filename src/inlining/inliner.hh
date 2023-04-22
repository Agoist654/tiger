/**
 ** \file inlining/inliner.hh
 ** \brief Declaration of inlining::Inliner.
 */

#pragma once

#include <map>

#include <astclone/cloner.hh>
#include <misc/scoped-map.hh>
#include <misc/set.hh>

namespace inlining
{
  /// Perform inline expansion of functions.
  class Inliner : public astclone::Cloner
  {
  public:
    using super_type = astclone::Cloner;

    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build an Inliner.
    Inliner(const ast::Ast& tree);

    /// \name Visit methods.
    /// \{
    // FIXME: Some code was deleted here.
<<<<<<< HEAD
    void operator()(const ast::CallExp& e) override;
    void operator()(const ast::FunctionChunk& e) override;
    void operator()(const ast::FunctionDec& e) override;

=======
>>>>>>> afe1cdc (2025-tc-4.0.)
    /// \}

    /// \name Getters.
    /// \{
    const misc::set<const ast::FunctionDec*>& rec_funs_get() const;
    /// \}

  private:
    /// Recursive functions of the program.
    misc::set<const ast::FunctionDec*> rec_funs_;
  };

} // namespace inlining
