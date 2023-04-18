/**
 ** \file ast/class-ty.hxx
 ** \brief Inline methods of ast::ClassTy.
 */

#pragma once

#include <ast/class-ty.hh>

namespace ast
{

  inline const NameTy& ClassTy::super_get() const { return *super_; }
  inline NameTy& ClassTy::super_get() { return *super_; }

  inline const ChunkList& ClassTy::chunks_get() const { return *chunks_; }
  inline ChunkList& ClassTy::chunks_get() { return *chunks_; }

  inline const TypeDec* ClassTy::def_get() const { return def_; }
  inline TypeDec* ClassTy::def_get() { return def_; }
  inline void ClassTy::def_set(TypeDec* def) { def_ = def; }

  


} // namespace ast
