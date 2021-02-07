#pragma once
#include "Logging/Logger.h"
#include <Windows.h>

class DebugLogger : public junjinjen_matrix::firmware::logging::Logger
{
public:
	~DebugLogger();

	void Log(const std::string& msg) const;
	void Log(const char* buffer, size_t length) const;

	// Inherited via Logger
	virtual void LogInfo(const std::string& msg) const override;
	virtual void LogInfo(const char* buffer, size_t length) const override;
	virtual void LogError(const std::string& msg) const override;
	virtual void LogError(const char* buffer, size_t length) const override;
	virtual void LogFatal(const std::string& msg) const override;
	virtual void LogFatal(const char* buffer, size_t length) const override;
	virtual void LogWarning(const std::string& msg) const override;
	virtual void LogWarning(const char* buffer, size_t length) const override;
};