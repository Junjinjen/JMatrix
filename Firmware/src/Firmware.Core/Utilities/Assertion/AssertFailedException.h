#pragma once
#include <stdexcept>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace utilities
		{
			namespace assertion
			{
				class AssertFailedException : public std::runtime_error
				{
				public:
					AssertFailedException(const std::string& assertion)
						: std::runtime_error("Assertion " + assertion + " failed")
					{
					}
				};
			}
		}
	}
}
