/**
 ** \file type/type.hxx
 ** \brief Inline methods for type::Type.
 */
#pragma once

#include <misc/contract.hh>
#include <type/type.hh>

namespace type
{
  inline bool operator==(const Type& lhs, const Type& rhs)
  {
    // FIXME: Some code was deleted here.
    ///*DONE*/
        return lhs.actual() == rhs.actual();
  }

  inline bool operator!=(const Type& lhs, const Type& rhs)
  {
    // FIXME: Some code was deleted here.
      ///*DONE*/
      return lhs.actual() != rhs.actual();
  }

} // namespace type
