#pragma once
#include <stdexcept>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace messaging
		{
			namespace exceptions
			{
				class InvalidTypeException : public std::runtime_error
				{
				public:
					InvalidTypeException()
						: std::runtime_error("Type mismatch occurred")
					{
					}
				};
			}
		}
	}
}
