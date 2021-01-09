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
