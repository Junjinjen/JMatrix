#include "MockClient.h"

MockClient::MockClient()
    : isClosed_(false), isConnected_(true), maxAcceptablePackageSize_(SIZE_MAX)
{
}

void MockClient::AddMessage(const std::string& msg)
{
    messagesBuffer_.push_back(GenerateMessage(&msg[0], msg.size()));
}

void MockClient::AddRawMessage(const std::string& msg)
{
    messagesBuffer_.push_back(msg);
}

void MockClient::AddMessage(const std::string& msg, size_t& packagesCount, bool& isSizePackageIncludesNextPartionData)
{
    auto buffer = GenerateMessage(&msg[0], msg.size());
    if (packagesCount > buffer.size())
    {
        packagesCount = buffer.size();
    }

    size_t pacakgeSize = buffer.size() / packagesCount;
    for (size_t i = 0; i < packagesCount - 1; i++)
    {
        messagesBuffer_.push_back(buffer.substr(i * pacakgeSize, pacakgeSize));
    }

    auto offset = pacakgeSize * (packagesCount - 1);
    messagesBuffer_.push_back(buffer.substr(offset));

    if (pacakgeSize > sizeof(size_t))
    {
        isSizePackageIncludesNextPartionData = true;
    }
    else
    {
        isSizePackageIncludesNextPartionData = false;
    }
}

void MockClient::SetMaxPackageSize(size_t size)
{
    maxAcceptablePackageSize_ = size;
}

std::vector<byte_string>& MockClient::GetOutput()
{
    return outputMessages_;
}

bool MockClient::DataAvaible()
{
    return !messagesBuffer_.empty();
}

bool MockClient::Connected()
{
    return isConnected_;
}

void MockClient::SetConnected(bool state)
{
    isConnected_ = state;
}

void MockClient::Close()
{
    isClosed_ = true;
    isConnected_ = false;
}

int32_t MockClient::Read(uint8_t* buffer, int32_t buffLength)
{
    size_t size = 0;
    if (!messagesBuffer_.empty())
    {
        auto msg = messagesBuffer_.front();
        
        if (msg.size() <= buffLength)
        {
            size = msg.size();
            memcpy(buffer, &msg[0], size);
            messagesBuffer_.erase(messagesBuffer_.begin());
        }
        else
        {
            size = buffLength;
            memcpy(buffer, &msg[0], size);
            messagesBuffer_[0] = msg.substr(size);
        }
    }

    return size;
}

int32_t MockClient::Write(const uint8_t* data, int32_t length)
{
    if (length > maxAcceptablePackageSize_)
    {
        length = maxAcceptablePackageSize_;
    }

    outputMessages_.push_back(byte_string(data, length));
    return length;
}

std::string MockClient::GenerateMessage(const char* buffer, size_t size)
{
    size_t packageSize = size + sizeof(size_t);
    char* msgBuffer = new char[packageSize];

    std::memcpy(msgBuffer, &size, sizeof(size_t));
    std::memcpy(msgBuffer + sizeof(size_t), buffer, size);

    std::string answ(msgBuffer, packageSize);
    delete[] msgBuffer;

    return answ;
}

std::string MockClient::GenerateMessage(const std::string& msg)
{
    return GenerateMessage(&msg[0], msg.size());
}
