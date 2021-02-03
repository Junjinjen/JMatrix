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
				class ContainerParseException : public std::runtime_error
				{
				public:
					ContainerParseException()
						: std::runtime_error("Unable to parse container")
					{
					}

					ContainerParseException(const std::string& message)
						: std::runtime_error(message)
					{
					}
				};
			}
		}
	}
}