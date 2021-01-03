#pragma once
#include <cstdint>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace network_pipeline
		{
			namespace network
			{
				class NetworkClient
				{
				public:
					virtual ~NetworkClient() = default;

					virtual bool DataAvaible() = 0;
					virtual bool Connected() = 0;
					virtual void Close() = 0;

					virtual size_t Read(void* buffer, size_t buffLength) = 0;
					virtual size_t Write(void* data, size_t length) = 0;
				};
			}
		}
	}
}