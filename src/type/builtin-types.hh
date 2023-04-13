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
    class String:public  misc::Singleton<String>, public Type
    {
        Singleton<String>& Singleton<String>::instance()
        {
            static const Singleton<String> instance(std::string("string"));
            return instance;
        }
    }
    class Int:public  misc::Singleton<Int>, public Type
    {
        Singleton<Int>& Singleton<Int>::instance()
        {
            static const Singleton<Int> instance(std::string("int"));
            return instance;
        }
    }
    class Void:public  misc::Singleton<Void>, public Type
               class Void
    {
        Singleton<Void>& Singleton<Void>::instance()
        {
            static const Singleton<Void> instance(std::string("void"));
            return instance;
        }
    }






} // namespace type
