/**
 ** \file type/record.cc
 ** \brief Implementation for type/record.hh.
 */

#include <ostream>

#include <type/builtin-types.hh>
#include <type/nil.hh>
#include <type/record.hh>
#include <type/visitor.hh>

namespace type
{
  void Record::accept(ConstVisitor& v) const { v(*this); }

  void Record::accept(Visitor& v) { v(*this); }

  // FIXME: Some code was deleted here (Field manipulators).
  const Type* field_type(misc::symbol key) const
  {
      for (Field& field : fields_)
      {
          if (field.name_get() == key)
            return field.type_get().actual();
      }
      return nullptr;
  }

  int field_index(misc::symbol key) const
  {
      int index = 0;
      for (Field& field : fields_)
      {
          if (field.name_get() == key)
              return index;
          index++;
      }
  }

  // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Record).
  /*bool compatible_with(const Type& other) const
  {
      return this->actual() == other || other == nil; //soit l'autre type est egal,
                                                      //...soit il est nil
  }*/
  bool Record::compatible_with(const Type& other) const
  {
    if (other.is_record()) {
      auto& other_record = dynamic_cast<const Record&>(other);
      if (fields_.size() == other_record.fields_.size()) {
        for (std::size_t i = 0; i < fields_.size(); ++i) {
          if (fields_[i].name != other_record.fields_[i].name
              || !fields_[i].type->compatible_with(*other_record.fields_[i].type)) {
            return false;
          }
        }
        return true;
      }
    }
    return false;
  }

} // namespace type
