/**
 ** \file type/builtin-types.hh
 ** \brief The classes Int, String, Void.
 */
#pragma once

#include <misc/singleton.hh>
#include <type/fwd.hh>
#include <type/type.hh>
#include <string>
namespace type
{
    // FIXME: Some code was deleted here (Other types : Int, String, Void)

///String
//
    class String : public  misc::Singleton<String>
                    , public Type
    {

    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    };

///Int
//
    class Int : public  misc::Singleton<Int>
                 , public Type
    {
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
        /*public:

            ~Int();
            void type_set(const type::Type*);

        private:
            const type::Type* type_;*/
    };

///Void
//
    class Void : public  misc::Singleton<Void>
                  , public Type
    {

    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    };

} // namespace type
