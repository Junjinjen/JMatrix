#pragma once
#include "Logging/Logger.h"
#include <Windows.h>

class DebugLogger : public junjinjen_matrix::firmware::logging::Logger
{
public:
	~DebugLogger();

	virtual void Log(const std::string& msg) const override;
	virtual void Log(const char* buffer, size_t length) const override;
};