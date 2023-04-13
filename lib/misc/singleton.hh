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
        Singleton& operator=(Singleton&&) = delete;
        static const Singleton& instance()
        {
            static T instance;
            return instance;
        }

    private:
        Singleton() = default;
    };

} // namespace misc
