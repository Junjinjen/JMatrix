#include "Pipe.h"

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
						Pipe::Pipe(NetworkClient* client)
							: client_(client), isClosed_(false)
						{
							logger_->LogInfo("Pipe created");
						}

						Pipe::Pipe(Pipe&& other) noexcept
							: logger_(std::move(other.logger_)), serializer_(std::move(other.serializer_)), messages_(std::move(other.messages_)),
							currentMessage_(std::move(other.currentMessage_)), readSize_(other.readSize_), messageSize_(other.messageSize_),
							isClosed_(other.isClosed_), client_(other.client_)
						{
							other.client_ = nullptr;
							other.messageSize_ = 0;
							other.readSize_ = 0;
							other.isClosed_ = false;
						}

						Pipe::~Pipe()
						{
							Close();
						}

						void Pipe::operator=(Pipe&& other) noexcept
						{
							logger_ = std::move(other.logger_);
							serializer_ = std::move(other.serializer_);
							messages_ = std::move(messages_);
							currentMessage_ = std::move(currentMessage_);

							readSize_ = other.readSize_;
							other.readSize_ = 0;

							messageSize_ = other.messageSize_;
							other.messageSize_ = 0;

							isClosed_ = other.isClosed_;
							other.isClosed_ = false;

							client_ = other.client_;
							other.client_ = nullptr;
						}

						bool Pipe::Connected() const
						{
							return !isClosed_ && client_->Connected();
						}

						void Pipe::Close()
						{
							if (!isClosed_)
							{
								client_->Close();
								delete client_;
								isClosed_ = true;

								logger_->LogInfo("Pipe closed");
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
							JUNJINJEN_ASSERT(!messages_.empty());
							auto&& message = std::move(messages_.front());
							messages_.pop();

							return message;
						}

						bool Pipe::SendMessage(const DataContainer& message) const
						{
							if (Connected())
							{
								byte_string string;
								if (serializer_->Serialize(message, string))
								{
									logger_->LogInfo(std::string("Sending message through pipe: [") + reinterpret_cast<const char*>(&string[0]) + "]");

									int32_t size = string.size();
									if (client_->Write((const uint8_t*)&size, sizeof(int32_t)) == sizeof(int32_t))
									{
										return client_->Write(&string[0], string.size()) == string.size();
									}
								}
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

										logger_->LogInfo(std::string("Pipe received message: [") + reinterpret_cast<const char*>(&currentMessage_[0]) + "]");

										DataContainer container;
										if (serializer_->Deserialize(currentMessage_, container))
										{
											logger_->LogInfo("Message deserialize successfully");
											messages_.push(std::move(container));
										}
										else
										{
											logger_->LogError("Message deserialization failed");
											SendMessage(DeserializationFailed());
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
