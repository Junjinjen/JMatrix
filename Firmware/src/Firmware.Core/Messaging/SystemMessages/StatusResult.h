#pragma once
#include "Messaging/DataContainer/DataContainer.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace messaging
		{
			namespace system_messages
			{
				class StatusResult : public DataContainer
				{
				public:
					StatusResult(bool isSuccessful)
					{
						SetBoolean("success", isSuccessful);
					}

					StatusResult(bool isSuccessful, const std::string& message)
						: StatusResult(isSuccessful)
					{
						SetString("message", message);
					}
				};
			}
		}
	}
}