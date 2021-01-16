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

					virtual int32_t Read(uint8_t* buffer, int32_t buffLength) = 0;
					virtual int32_t Write(const uint8_t* data, int32_t length) = 0;
				};
			}
		}
	}
}