/**
 ** \file misc/singleton.hh
 ** \brief Generic singleton
 */

#pragma once

namespace misc
{
    template <typename T>
    class Singleton
    {
        // FIXME: Some code was deleted here.
    public:
        Singleton(const Singleton&) = delete;
        Singleton(Singleton&&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton& operator=(Singleton&) = delete;
        static const T& instance()
        {

            static T* instance = new T;
            return *instance;
        }

    protected:
        Singleton() = default;
    };

} // namespace misc
