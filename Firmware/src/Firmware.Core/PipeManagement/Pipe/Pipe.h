#pragma once
#include "Logger/Logger.h"
#include "Network/NetworkServer.h"
#include <cstring>
#include <queue>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace pipe_management
		{
			using logger::Logger;
			using network::NetworkClient;
			using byte_string = std::basic_string<uint8_t>;

			class Pipe
			{
			public:
				Pipe(std::shared_ptr<Logger> logger, std::unique_ptr<NetworkClient> client);
				~Pipe();

				bool IsConnected();
				void Close();

				bool HasNewMessage();
				byte_string GetNewMessage();

				bool SendMessage(const byte_string& message);
				bool SendMessage(const std::string& message);

				byte_string currentMessage_;
			private:
				inline void ReadMessages();

				std::shared_ptr<Logger> logger_;
				std::unique_ptr<NetworkClient> client_;
				bool isClosed_;

				std::queue<byte_string> messages_;

				size_t readSize_;
				size_t messageSize_;

			};
		}
	}
}