/** \file misc/scoped-map.hxx
 ** \brief Implementation of misc::scoped_map.
 */

#pragma once

#include <sstream>
#include <stdexcept>
#include <type_traits>

#include <ranges>
#include <misc/algorithm.hh>
#include <misc/contract.hh>
#include <misc/indent.hh>

namespace misc
{
  // FIXME: Some code was deleted here.
    /*ONGOING*/
    template <typename Key, typename Data>
  void scoped_map<Key, Data>::put(const Key& key, const Data& value)
  {
      scope_.back()[key] = value;
  }

    template <typename Key, typename Data>
  Data scoped_map<Key, Data>::get(const Key& key) const
  {
      try {
          return scope_.back().find(key)->second;
      } catch (const std::invalid_argument& e) {
      if constexpr (std::is_pointer_v<Data>)
        return nullptr;
      else
        throw std::range_error("Data is a value type");
      }
  }

    template <typename Key, typename Data>
  std::ostream& scoped_map<Key, Data>::dump(std::ostream& ostr) const
  {
      for (auto& elt : scope_.back)
      {
          ostr << elt->first << " : " << elt->second << '\n';
      }
      return ostr;
  }

    template <typename Key, typename Data>
  void scoped_map<Key, Data>::scope_begin()
  {
      if (scope_.empty())
      {
          std::map<Key, Data> m;
          scope_.push_back(m);
      }

      else
        scope_.push_back(scope_.back());
  }

    template <typename Key, typename Data>
  void scoped_map<Key, Data>::scope_end()
  {
      if (scope_.empty())
          return;
      scope_.pop_back();
  }

  template <typename Key, typename Data>
  inline std::ostream& operator<<(std::ostream& ostr,
                                  const scoped_map<Key, Data>& tbl)
  {
    return tbl.dump(ostr);
  }



//
  template<typename Key, typename Data>
  inline std::map<Key, Data> scoped_map<Key, Data>::get_back_map() const
  {
      return scope_.back();
  }

  template<typename Key, typename Data>
  inline std::vector<std::map<Key, Data>> scoped_map<Key, Data>::get_vector() const
  {
      return scope_;
  }




} // namespace misc
