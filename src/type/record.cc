/**
 ** \file type/record.cc
 ** \brief Implementation for type/record.hh.
 */

#include <ostream>

#include <type/builtin-types.hh>
#include <type/nil.hh>
#include <type/record.hh>
#include <type/visitor.hh>

namespace type {
    void Record::accept(ConstVisitor &v) const { v(*this); }

    void Record::accept(Visitor &v) { v(*this); }

    // FIXME: Some code was deleted here (Field manipulators).
    const Type* Record::field_type(misc::symbol key) const {
        for (const Field& field: fields_) {
            if (field.name_get() == key)
                return &field.type_get();
        }
        return nullptr;
    }

    int Record::field_index(misc::symbol key) const {
        int index = 0;
        for (const Field& field: fields_) {
            if (field.name_get() == key)
                return index;
            index++;
        }
        return -1;
    }

    // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Record).
    /*bool compatible_with(const Type& other) const
    {
        return this->actual() == other || other == nil; //soit l'autre type est egal,
                                                        //...soit il est nil
    }*/
    bool Record::compatible_with(const Type &other) const {
        if (dynamic_cast<const Nil*>(&other))
            return true;
        const Record& other_record = dynamic_cast<const Record&>(other.actual());
        if (other_record == other)
            return *this == other_record;
        return false;
    }
} // namespace type
