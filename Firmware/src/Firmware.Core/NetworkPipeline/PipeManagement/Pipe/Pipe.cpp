#include "Pipe.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace network_pipeline
		{
			namespace pipe_management
			{
				Pipe::Pipe(std::shared_ptr<Logger> logger, std::unique_ptr<NetworkClient> client)
					: logger_(logger), client_(std::move(client)), isClosed_(false), readSize_(0), messageSize_(0)
				{
					logger_->Log("Pipe created");
				}

				Pipe::~Pipe()
				{
					Close();
				}

				bool Pipe::IsConnected() const
				{
					if (!isClosed_)
					{
						return client_->Connected();
					}

					return false;
				}

				bool Pipe::HasNewMessage()
				{
					if (IsConnected())
					{
						ReadMessages();
						return !messages_.empty();
					}

					return false;
				}

				void Pipe::Close()
				{
					if (!isClosed_)
					{
						client_->Close();
						client_.reset();

						isClosed_ = true;
						logger_->Log("Pipe closed");
					}
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

					return byte_string();
				}

				bool Pipe::SendMessage(const uint8_t* message, int32_t size)
				{
					if (size == 0)
					{
						return true;
					}

					if (size < 0 || !IsConnected())
					{
						return false;
					}

					logger_->Log(std::string("Sending message through pipe: [") + reinterpret_cast<const char*>(message) + "]");

					int32_t msgSize = size;
					size_t left = sizeof(int32_t);
					while (left > 0 && client_->Connected())
					{
						left -= client_->Write(((uint8_t*)&msgSize) + sizeof(int32_t) - left, left);
					}

					if (left == 0)
					{
						size_t left = msgSize;
						while (left > 0 && client_->Connected())
						{
							left -= client_->Write(&message[msgSize - left], left);
						}

						return left == 0;
					}
					
					return false;
				}

				bool Pipe::SendMessage(const std::string& message)
				{
					if (message.empty())
					{
						return true;
					}

					return SendMessage(byte_string(message.begin(), message.end()));
				}

				bool Pipe::SendMessage(const byte_string& message)
				{
					if (message.empty())
					{
						return true;
					}

					return SendMessage(&message[0], message.size());
				}

				void Pipe::ReadMessages()
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
