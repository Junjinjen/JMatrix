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
				class SerializationFailed : public StatusResult
				{
				public:
					SerializationFailed()
						: StatusResult(false, "Message serialization failed")
					{
					}

					SerializationFailed(const std::string& message)
						: StatusResult(false, message)
					{
					}
				};
			}
		}
	}
}
