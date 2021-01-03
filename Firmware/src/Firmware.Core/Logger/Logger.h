#pragma once
#include <string>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace logger
		{
			class Logger
			{
			public:
				virtual ~Logger() = default;

				virtual void Initialize() { }

				virtual void Log(const std::string& msg) const = 0;

				virtual void Log(const char* buffer, size_t length) const = 0;
			};
		}
	}
}