#include "DebugLogger.h"

DebugLogger::~DebugLogger()
{
	Log("Logger stopped");
}

void DebugLogger::Log(const std::string& msg) const
{
	std::wstring tmp(msg.begin(), msg.end());
	tmp += L"\n";
	OutputDebugString(&tmp[0]);
}

void DebugLogger::Log(const char* buffer, size_t length) const
{
	Log(std::string(buffer, length));
}

void DebugLogger::LogInfo(const std::string& msg) const
{
	Log(msg);
}

void DebugLogger::LogInfo(const char* buffer, size_t length) const
{
	Log(buffer, length);
}

void DebugLogger::LogError(const std::string& msg) const
{
	Log(msg);
}

void DebugLogger::LogError(const char* buffer, size_t length) const
{
	Log(buffer, length);
}

void DebugLogger::LogFatal(const std::string& msg) const
{
	Log(msg);
}

void DebugLogger::LogFatal(const char* buffer, size_t length) const
{
	Log(buffer, length);
}
