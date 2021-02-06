#include "CppUnitTest.h"
#include "DependencyInjection/ContainerBuilder/ContainerBuilder.h"
#include "NetworkPipeline/PipeManagement/PipeManager/PipeManager.h"
#include "../../Mocks/Logger/DebugLogger.h"
#include "../../Mocks/Network/Server/MockServer.h"
#include "../../Mocks/Network/Client/MockClient.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace junjinjen_matrix::firmware::network::pipe_management;
using namespace junjinjen_matrix::firmware::dependency_injection;

namespace PipeManagementUnitTests
{
	class ContainerSerializerStub : public ContainerSerializer
	{
	public:
		virtual bool Serialize(const DataContainer& container, byte_string& outputBuffer) override
		{
			return false;
		}

		virtual bool Deserialize(const byte_string& inputBuffer, DataContainer& container) override
		{
			return false;
		}
	};

	TEST_CLASS(PipeManagerUnitTests)
	{
	public:
		TEST_CLASS_INITIALIZE(InitializeIocContainer)
		{
			ContainerBuilder builder;
			auto server = new MockServer();
			builder.AddSingleton<DebugLogger, junjinjen_matrix::firmware::logging::Logger>();
			builder.AddSingleton<ContainerSerializerStub, ContainerSerializer>();
			builder.AddSingleton<MockServer, NetworkServer>(server);
			builder.AddSingleton<MockServer>(server);
			builder.Build();
		}

		TEST_METHOD(HasNewPipe_WhenServerHasNewClient_ReturnsTrue)
		{
			// Arrange
			auto [server, pipeManager] = ConfigureTestPipeManager();
			server->AddClient(new MockClient());

			// Act / Assert
			Assert::IsTrue(server->HasNewClient());
		}

		TEST_METHOD(HasNewPipe_WhenServerHasNotNewClient_ReturnsFalse)
		{
			// Arrange
			auto [server, pipeManager] = ConfigureTestPipeManager();

			// Act / Assert
			Assert::IsFalse(server->HasNewClient());
		}

		TEST_METHOD(GetNewPipe_WhenServerHasNewClient_AssertPassed)
		{
			// Arrange
			auto [server, pipeManager] = ConfigureTestPipeManager();
			server->AddClient(new MockClient());

			// Act / Assert
			auto pipe = pipeManager->GetNewPipe();
		}

		TEST_METHOD(GetNewPipe_WhenServerHasNotNewClient_AssertFailed)
		{
			// Arrange
			auto [server, pipeManager] = ConfigureTestPipeManager();

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { pipeManager->GetNewPipe(); });
		}
	private:
		inline std::tuple<std::shared_ptr<MockServer>, std::unique_ptr<PipeManager>> ConfigureTestPipeManager()
		{
			auto server = RESOLVE_INSTANCE(MockServer);
			auto pipe = std::make_unique<PipeManager>();

			return std::make_tuple(server, std::move(pipe));
		}
	};
}