#pragma once
#include "NetworkClient.h"
#include <memory>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace network
		{
			class NetworkServer
			{
			public:
				virtual ~NetworkServer() = default;

				virtual bool Initialize(uint16_t port) = 0;
				virtual void Stop() = 0;

				virtual bool HasNewClient() = 0;
				virtual std::unique_ptr<NetworkClient> GetNewClient() = 0;
			};
		}
	}
}