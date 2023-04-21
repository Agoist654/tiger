/**
 ** \file type/class.cc
 ** \brief Implementation for type/class.hh.
 */

#include <ostream>

#include <misc/algorithm.hh>
#include <type/class.hh>
#include <type/visitor.hh>

namespace type
{
  Class::Class(const Class* super)
    : Type()
    , id_(fresh_id())
    , super_(super)
    , subclasses_()
  {}

  void Class::accept(ConstVisitor& v) const { v(*this); }

  void Class::accept(Visitor& v) { v(*this); }

  const Type* Class::attr_type(misc::symbol key) const
  {
    // FIXME: Some code was deleted here.
    /*notes : attrs_ est std::vector<Attribute>
     * meths_ est std::vector<const Method*>
     * subclasses_ est std::vector<const Class*> */
    ///DONE
    for (const Attribute att : this->attrs_get())
    {
        if (att.name_get() == key)
            return &att.type_get();
    }
  }

  const Type* Class::meth_type(misc::symbol key) const
  {
    // FIXME: Some code was deleted here.
    ///DONE
      for (const Method* met : this->meths_get())
      {
          if (met->name_get() == key)
              return &met->type_get();
      }
  }

  // FIXME: Some code was deleted here (Find common super class).
  ///DONE
  /*const Class* common_root(const Class& other) const
  {
      Class* tracker = this;
      std::set<Class*> supers;
      while (tracker != nullptr)
      {
          supers.insert(tracker->super_get());
          tracker = tracker->super_get();
      }
      tracker = &*other;
      while (supers.insert(tracker).second)
          tracker = tracker->super_get();
      return tracker;
  }*/

  // FIXME: Some code was deleted here (Super class soundness test).
  ///DONE
  bool Class::sound() const
  {
      for (const Class* sub : subclasses_get())
      {
          if (sub == this)
              return false;
      }
      return true;
  }

  // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Class).
  ///DONE
  bool Class::compatible_with(const Type& other) const
  {
      ///return this->id_get() == other.id_get(); ///pas bon, corriger dans record d'abord
      const Class& other_class = dynamic_cast<const Class&>(other);
      if (other_class != other)
          return false;
      return subclasses_ == other_class.subclasses_get();
  }

  const Class& Class::object_instance()
  {
    // FIXME: Some code was deleted here.
    ///
  }

  unsigned Class::fresh_id()
  {
    static unsigned counter_ = 0;
    return counter_++;
  }

} // namespace type
