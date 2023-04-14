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
    class Int:public  misc::Singleton<Int>, public Type
    class Void:public  misc::Singleton<Void>, public Type
} // namespace type
