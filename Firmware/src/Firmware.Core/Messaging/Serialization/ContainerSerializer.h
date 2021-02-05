#pragma once
#include "Messaging/DataContainer/DataContainer.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace messaging
		{
			namespace serialization
			{
				class ContainerSerializer
				{
				public:
					virtual ~ContainerSerializer() = default;

					virtual bool Serialize(const DataContainer& container, byte_string& outputBuffer) = 0;
					virtual bool Deserialize(const byte_string& inputBuffer, DataContainer& container) = 0;
				};
			}
		}
	}
}
