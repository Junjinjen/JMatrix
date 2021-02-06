#pragma once
#include "Utilities/ByteDefinitions/ByteDefinitions.h"
#include "Services/TaskService/NetworkPipeline/Network/NetworkClient.h"
#include <vector>
#include <string>

using junjinjen_matrix::firmware::services::task_service::network_pipeline::network::NetworkClient;
using junjinjen_matrix::firmware::utilities::byte_definitions::byte_string;

class MockClient : public NetworkClient
{
public:
	MockClient();

	void AddMessage(const std::string& msg);
	void AddRawMessage(const std::string& msg);
	void AddMessage(const std::string& msg, size_t& packagesCount, bool& isSizePackageIncludesNextPartionData);
	std::string GenerateMessage(const char* buffer, size_t size);
	std::string GenerateMessage(const std::string& msg);

	void SetMaxPackageSize(size_t size);
	std::vector<byte_string>& GetOutput();

	virtual bool DataAvaible() override;

	virtual bool Connected() override;
	void SetConnected(bool state);

	virtual void Close() override;

	virtual int32_t Read(uint8_t* buffer, int32_t buffLength) override;
	virtual int32_t Write(const uint8_t* data, int32_t length) override;
private:
	std::vector<byte_string> outputMessages_;
	std::vector<std::string> messagesBuffer_;
	bool isClosed_;
	bool isConnected_;
	size_t maxAcceptablePackageSize_;
};
