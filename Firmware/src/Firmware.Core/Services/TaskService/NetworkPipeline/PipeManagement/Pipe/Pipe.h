#pragma once
#include "Logging/Logger.h"
#include "DependencyInjection/Container/Container.h"
#include "Messaging/Serialization/ContainerSerializer.h"
#include "Messaging/SystemMessages/SerializationFailed.h"
#include "Messaging/SystemMessages/DeserializationFailed.h"
#include "Services/TaskService/NetworkPipeline/Network/NetworkClient.h"
#include "Utilities/ByteDefinitions/ByteDefinitions.h"
#include <cstdint>
#include <queue>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace services
		{
			namespace task_service
			{
				namespace network_pipeline
				{
					namespace pipe_management
					{
						using logging::Logger;
						using network::NetworkClient;
						using messaging::DataContainer;
						using messaging::serialization::ContainerSerializer;
						using messaging::system_messages::SerializationFailed;
						using messaging::system_messages::DeserializationFailed;
						using utilities::byte_definitions::byte_string;

						class Pipe
						{
						public:
							Pipe(NetworkClient* client);
							Pipe(const Pipe& other) = delete;
							Pipe(Pipe&& other) noexcept;
							~Pipe();

							void operator=(Pipe&& other) noexcept;
							void operator=(const Pipe& other) = delete;

							bool Connected() const;
							void Close();

							bool HasNewMessage();
							DataContainer GetNewMessage();

							bool SendMessage(const DataContainer& message) const;
						private:
							INJECT_FIELD(Logger, logger_)
							INJECT_FIELD(ContainerSerializer, serializer_)
							NetworkClient* client_;
							bool isClosed_;

							std::queue<DataContainer> messages_;

							inline void ReadMessages();

							size_t readSize_;
							int32_t messageSize_;
							byte_string currentMessage_;
						};
					}
				}
			}
		}
	}
}
