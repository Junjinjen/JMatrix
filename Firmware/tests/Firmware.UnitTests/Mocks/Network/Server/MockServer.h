#pragma once
#include "Services/TaskService/NetworkPipeline/Network/NetworkServer.h"
#include <queue>

using junjinjen_matrix::firmware::services::task_service::network_pipeline::network::NetworkClient;
using junjinjen_matrix::firmware::services::task_service::network_pipeline::network::NetworkServer;

class MockServer : public NetworkServer
{
public:
	MockServer();
	~MockServer();

	void SetInitializationResult(bool initializationResult);
	void AddClient(NetworkClient* client);

	virtual bool Initialize() override;
	virtual void Stop() override;

	virtual bool HasNewClient() override;
	virtual NetworkClient* GetNewClient() override;
private:
	std::queue<NetworkClient*> clients_;
	bool initResult_;
};