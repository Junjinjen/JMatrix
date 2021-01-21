#pragma once
#include <cstdint>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace task_management
		{
			enum class StatusCode : uint8_t
			{
				Success			= 0b00000001,
				UndefinedError	= 0b00000010,
				TaskNotFound	= 0b00000100,
			};
		}
	}
}
