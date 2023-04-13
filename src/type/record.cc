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
      for (Field& field : fields)
      {
          if (field.name_get() == key)
            return field.type_get().actual();
      }
      return nullptr;
  }

  int field_index(misc::symbol key) const
  {
      int index = 0;
      for (Field& field : fields)
      {
          if (field.name_get() == key)
              return index;
          index++;
      }
  }

  // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Record).
  bool compatible_with(const Type& other) const
  {
      Record& otherRec = dynamic_cast<Record&>(other);
      return other.fields_get() == this->fields_get();
  }

} // namespace type
