#pragma once
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
					Pipe(std::shared_ptr<Logger> logger, std::unique_ptr<NetworkClient> client);
					~Pipe();

					bool IsConnected() const;
					void Close();

					bool HasNewMessage();
					byte_string GetNewMessage();

					bool SendMessage(const uint8_t* message, int32_t size);
					bool SendMessage(const std::string& message);
					bool SendMessage(const byte_string& message);
				private:
					inline void ReadMessages();

					std::shared_ptr<Logger> logger_;
					std::unique_ptr<NetworkClient> client_;
					bool isClosed_;

					std::queue<byte_string> messages_;

					size_t readSize_;
					int32_t messageSize_;
					byte_string currentMessage_;
				};
			}
		}
	}
}