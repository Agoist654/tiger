/**
 ** \file misc/symbol.hxx
 ** \brief Inline implementation of misc::symbol.
 */

#pragma once

#include <misc/symbol.hh>

namespace misc
{
  inline symbol& symbol::operator=(const symbol& rhs)
  {
    // FIXME: Some code was deleted here.
//DONE

    unique::operator=(rhs);
    return *this;
  }

  inline bool symbol::operator==(const symbol& rhs) const
  {
    // FIXME: Some code was deleted here.
    //DONE
    if (unique::operator==(rhs))
        return true;
    return false;
  }

  inline bool symbol::operator!=(const symbol& rhs) const
  {
    // FIXME: Some code was deleted here.
    // DONE
    return !operator==(rhs);
  }

  inline std::ostream& operator<<(std::ostream& ostr, const symbol& the)
  {
    // FIXME: Some code was deleted here.
    //DONE
    ostr << the.unique::get();
    return ostr;
  }

} // namespace misc
