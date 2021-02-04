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
				class DeserializationFailed : public StatusResult
				{
				public:
					DeserializationFailed()
						: StatusResult(false, "Message deserialization failed")
					{
					}

					DeserializationFailed(const std::string& message)
						: StatusResult(false, message)
					{
					}
				};
			}
		}
	}
}
