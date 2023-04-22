/**
 ** \file type/type.hxx
 ** \brief Inline methods for type::Type.
 */
#pragma once

#include <misc/contract.hh>
#include <type/type.hh>
#include <type/named.hh>

namespace type
{
  inline bool operator==(const Type& lhs, const Type& rhs)
  {
    // FIXME: Some code was deleted here.
    ///*DONE*/
   // auto l = dynamic_cast<const Named*>(&lhs);
   // if (l)
   //   std::cout << "lhs" << l->type_get() << "\n";
   // auto i = dynamic_cast<const Named*>(&rhs);
   // if (i)
   //   std::cout << "rhs" << i->type_get() << std::endl;
        return &lhs.actual() == &rhs.actual();
  }

  inline bool operator!=(const Type& lhs, const Type& rhs)
  {
    // FIXME: Some code was deleted here.
      ///*DONE*/
      return !(lhs == rhs);
  }

} // namespace type
