#pragma once
#include "Utilities/Assertion/AssertDefinition.h"
#include "Logging/Logger.h"
#include "DependencyInjection/Container/Container.h"
#include "Messaging/Serialization/ContainerSerializer.h"
#include "Utilities/ByteDefinitions/ByteDefinitions.h"
#include "NetworkPipeline/Network/NetworkServer.h"
#include "Messaging/SystemMessages/DeserializationFailed.h"
#include "Messaging/SystemMessages/SerializationFailed.h"
#include <queue>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace network
		{
			namespace pipe_management
			{
				using logging::Logger;
				using utilities::byte_definitions::byte_string;
				using messaging::serialization::ContainerSerializer;
				using messaging::DataContainer;
				using messaging::system_messages::DeserializationFailed;
				using messaging::system_messages::SerializationFailed;

				class Pipe
				{
				public:
					Pipe(NetworkClient* client);
					Pipe(Pipe&& pipe) noexcept = default;
					Pipe(const Pipe& pipe) = delete;
					~Pipe();

					void operator=(const Pipe& other) = delete;
					void operator=(Pipe&& other) noexcept;

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
					inline void SendSerializationFailedError() const;

					size_t readSize_;
					int32_t messageSize_;
					byte_string currentMessage_;
				};
			}
		}
	}
}