#pragma once
#ifdef JUNJINJEN_UNIT_TESTING
#include <stdexcept>

class AssertFailedException : public std::runtime_error
{
public:
	AssertFailedException(const std::string& assertion)
		: std::runtime_error("Assertion " + assertion + " failed")
	{
	}
};

#define JUNJINJEN_ASSERT(x) (!(x) ? throw AssertFailedException(#x) : (void)0u)
#else
#include <cassert>
#define JUNJINJEN_ASSERT(x) assert(x)
#endif