#pragma once
#include "Messaging/DataContainer/DataContainer.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace messaging
		{
			class ContainerProvider
			{
			public:
				virtual ~ContainerProvider() = default;

				virtual byte_string Pack(const DataContainer& container) = 0;
				virtual DataContainer Unpack(const byte_string& buffer) = 0;
			};
		}
	}
}
