/**
 ** \file type/array.hh
 ** \brief The class Array.
 */
#pragma once

#include <type/fwd.hh>
#include <type/type.hh>
#include <type/visitor.hh>

namespace type
{
    /// Array types.
    class Array : public Type
    {
        // FIXME: Some code was deleted here.
        public:
            explicit Array();
//            Array();
            Type& arrtype_get();

            void arrtype_set(const Type& type);
            void arrtype_set(Type& type);
            Type* arrtype_get() const ;

            bool compatible_with(const Type& other) const override;
            void accept(ConstVisitor& v) const override;
            void accept(Visitor& v) override;

        protected:
            Type* arrtype_{};
    };

} // namespace type

#include <type/array.hxx>
