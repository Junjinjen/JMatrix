#pragma once
#include <string>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace logging
		{
			class Logger
			{
			public:
				virtual ~Logger() = default;

				virtual void Initialize() { }

				virtual void LogInfo(const std::string& msg) const = 0;
				virtual void LogInfo(const char* buffer, size_t length) const = 0;

				virtual void LogError(const std::string& msg) const = 0;
				virtual void LogError(const char* buffer, size_t length) const = 0;

				virtual void LogFatal(const std::string& msg) const = 0;
				virtual void LogFatal(const char* buffer, size_t length) const = 0;
			};
		}
	}
}