#pragma once
#include "NetworkPipeline/Network/NetworkServer.h"
#include "NetworkPipeline/Network/NetworkClient.h"
#include <queue>

using junjinjen_matrix::firmware::network_pipeline::network::NetworkServer;
using junjinjen_matrix::firmware::network_pipeline::network::NetworkClient;

class MockServer : public NetworkServer
{
public:
	MockServer();
	~MockServer();

	void SetInitializationResult(bool initializationResult);
	void AddClient(NetworkClient* client);

	virtual bool Initialize(uint16_t port) override;
	virtual void Stop() override;

	virtual bool HasNewClient() override;
	virtual std::unique_ptr<NetworkClient> GetNewClient() override;
private:
	std::queue<NetworkClient*> clients_;
	bool initResult_;
};