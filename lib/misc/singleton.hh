/**
 ** \file misc/singleton.hh
 ** \brief Generic singleton
 */

#pragma once

#include <string>

namespace misc
{
	template <typename T> class Singleton
	{
		// FIXME: Some code was deleted here.
		public:
			Singleton(const Singleton&) = delete;
			Singleton(Singleton&&) = delete;
			Singleton& operator=(const Singleton&) = delete;
			Singleton& operator=(Singleton&&) = delete;
			static const Singleton& instance()
			{
				static Singleton instance;
				return instance;
			}
		private:
			Singleton() = default;
	};
	template <>
		Singleton<String>& Singleton<String>::instance()
		{
			static const Singleton<String> instance(std::string("string"));
			return instance;
		}




} // namespace misc
