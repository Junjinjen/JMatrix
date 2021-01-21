#include "Pipe.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace network_pipeline
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

				byte_string Pipe::GetNewMessage()
				{
					if (HasNewMessage())
					{
						byte_string message = std::move(messages_.front());
						messages_.pop();

						logger_->Log(std::string("Pipe returned message: [") + reinterpret_cast<const char*>(&message[0]) + "]");
						return message;
					}

					return nullptr;
				}

				bool Pipe::SendMessage(const byte_string& message)
				{
					if (Connected())
					{
						logger_->Log(std::string("Sending message through pipe: [") + reinterpret_cast<const char*>(&message[0]) + "]");

						int32_t size = message.size();
						if (client_->Write((const uint8_t*)&size, sizeof(int32_t)) == sizeof(int32_t))
						{
							return client_->Write(&message[0], message.size()) == message.size();
						}
						
						return false;
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
								messages_.emplace(&currentMessage_[0], messageSize_);
								messageSize_ = 0;
								readSize_ = 0;
							}
						}
					}
				}
			}
		}
	}
}
