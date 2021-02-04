#include "Pipe.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace network
		{
			namespace pipe_management
			{
				Pipe::Pipe(std::unique_ptr<NetworkClient> client)
					: isClosed_(false), client_(std::move(client))
				{
				}

				Pipe::~Pipe()
				{
					Close();
				}

				bool Pipe::Connected() const
				{
					if (client_->Connected() && !isClosed_)
					{
						return true;
					}

					return false;
				}

				void Pipe::Close()
				{
					if (!isClosed_)
					{
						client_->Close();
						isClosed_ = true;
						logger_->Log("Pipe closed");
					}
				}

				bool Pipe::HasNewMessage()
				{
					if (Connected())
					{
						ReadMessages();
						return !messages_.empty();
					}

					return false;
				}

				DataContainer Pipe::GetNewMessage()
				{
					JUNJINJEN_ASSERT(HasNewMessage());
					DataContainer message = std::move(messages_.front());
					messages_.pop();

					return message;
				}

				bool Pipe::SendMessage(const DataContainer& message)
				{
					if (!Connected())
					{
						return false;
					}

					byte_string string;
					if (!serializer_->Serialize(message, string))
					{
						logger_->Log("Message serialization failed");
						SendSerializationFailedError();
						return false;
					}
						
					logger_->Log(std::string("Sending message through pipe: [") + reinterpret_cast<const char*>(&string[0]) + "]");

					int32_t size = string.size();
					if (client_->Write((const uint8_t*)&size, sizeof(int32_t)) == sizeof(int32_t))
					{
						return client_->Write(&string[0], string.size()) == string.size();
					}

					return false;
				}

				inline void Pipe::ReadMessages()
				{
					if (client_->DataAvaible())
					{
						if (readSize_ < sizeof(int32_t))
						{
							readSize_ += client_->Read((uint8_t*)&messageSize_ + readSize_, sizeof(int32_t) - readSize_);
						}

						if (readSize_ >= sizeof(int32_t))
						{
							if (currentMessage_.size() != messageSize_)
							{
								currentMessage_.resize(messageSize_);
							}

							readSize_ += client_->Read(&currentMessage_[readSize_ - sizeof(int32_t)], messageSize_ - (readSize_ - sizeof(int32_t)));

							if (readSize_ == messageSize_ + sizeof(int32_t))
							{
								messageSize_ = 0;
								readSize_ = 0;

								DataContainer container;
								logger_->Log(std::string("Pipe returned message: [") + reinterpret_cast<const char*>(&currentMessage_[0]) + "]");
								if (serializer_->Deserialize(currentMessage_, container))
								{
									messages_.push(std::move(container));
								}
								else
								{
									logger_->Log("Message deserialization failed");
									SendMessage(DeserializationFailed());
								}
							}
						}
					}
				}

				inline void Pipe::SendSerializationFailedError()
				{
					byte_string string;
					if (serializer_->Serialize(SerializationFailed(), string))
					{
						client_->Write(&string[0], string.size());
					}
				}
			}
		}
	}
}
