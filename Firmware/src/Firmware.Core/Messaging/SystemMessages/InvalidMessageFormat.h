#pragma once
#include "StatusResult.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace messaging
		{
			namespace system_messages
			{
				class InvalidMessageFormat : public StatusResult
				{
				public:
					InvalidMessageFormat()
						: StatusResult(false, "Invalid message format")
					{
					}

					InvalidMessageFormat(const std::string& message)
						: StatusResult(false, message)
					{
					}
				};
			}
		}
	}
}
