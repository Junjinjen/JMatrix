#pragma once
#include "Network/NetworkClient.h"
#include "PipeManagement/Pipe/Pipe.h"
#include <vector>
#include <string>

using junjinjen_matrix::firmware::network::NetworkClient;

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
	std::vector<junjinjen_matrix::firmware::pipe_management::byte_string>& GetOutput();

	virtual bool DataAvaible() override;

	virtual bool Connected() override;
	void SetConnected(bool state);

	virtual void Close() override;

	virtual size_t Read(void* buffer, size_t buffLength) override;
	virtual size_t Write(void* data, size_t length) override;
private:
	std::vector<junjinjen_matrix::firmware::pipe_management::byte_string> outputMessages_;
	std::vector<std::string> messagesBuffer_;
	bool isClosed_;
	bool isConnected_;
	size_t maxAcceptablePackageSize_;
};
