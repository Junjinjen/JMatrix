#pragma once
#include "DependencyInjection/Container/Container.h"
#include "Logger/Logger.h"
#include "Utilities/ByteDefinitions/ByteDefinitions.h"
#include "NetworkPipeline/Network/NetworkServer.h"
#include <queue>
#include <cstring>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace network_pipeline
		{
			namespace pipe_management
			{
				using logger::Logger;
				using network::NetworkClient;
				using utilities::byte_definitions::byte_string;

				class Pipe
				{
				public:
					Pipe(std::unique_ptr<NetworkClient> client);
					~Pipe();

					bool Connected() const;
					void Close();

					bool HasNewMessage();
					byte_string GetNewMessage();
					bool SendMessage(const byte_string& message);
				private:
					INJECT_FIELD(Logger, logger_)
					std::unique_ptr<NetworkClient> client_;
					bool isClosed_;

					std::queue<byte_string> messages_;

					inline void ReadMessages();

					size_t readSize_;
					int32_t messageSize_;
					byte_string currentMessage_;
				};
			}
		}
	}
}