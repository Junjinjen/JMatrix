#include "MockServer.h"

MockServer::MockServer()
    : initResult_(true)
{
}

MockServer::~MockServer()
{
    Stop();
}

void MockServer::SetInitializationResult(bool initializationResult)
{
    initResult_ = initializationResult;
}

void MockServer::AddClient(NetworkClient* client)
{
    clients_.push(client);
}

bool MockServer::Initialize(uint16_t port)
{
    return initResult_;
}

void MockServer::Stop()
{
}

bool MockServer::HasNewClient()
{
    return !clients_.empty();
}

std::unique_ptr<NetworkClient> MockServer::GetNewClient()
{
    auto tmp = clients_.front();
    clients_.pop();
    return std::unique_ptr<NetworkClient>(tmp);
}
