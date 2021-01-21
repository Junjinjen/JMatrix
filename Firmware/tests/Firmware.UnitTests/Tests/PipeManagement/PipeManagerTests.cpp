#include "CppUnitTest.h"
#include "DependencyInjection/ContainerBuilder/ContainerBuilder.h"
#include "NetworkPipeline/PipeManagement/PipeManager/PipeManager.h"
#include "../../Mocks/Logger/DebugLogger.h"
#include "../../Mocks/Network/Server/MockServer.h"
#include "../../Mocks/Network/Client/MockClient.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace junjinjen_matrix::firmware::network_pipeline::pipe_management;
using namespace junjinjen_matrix::firmware::dependency_injection;

namespace JunjinjenMatrixUnitTests
{
	TEST_CLASS(PipeManagerUnitTests)
	{
	public:
		TEST_CLASS_INITIALIZE(InitializeIocContainer)
		{
			ContainerBuilder builder;
			builder.AddSingleton<DebugLogger, junjinjen_matrix::firmware::logger::Logger>();
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

		TEST_METHOD(GetNewPipe_WhenServerHasNewClient_ReturnsPipe)
		{
			// Arrange
			auto [server, pipeManager] = ConfigureTestPipeManager();
			server->AddClient(new MockClient());

			// Act
			auto pipe = pipeManager->GetNewPipe();

			// Assert
			Assert::IsNotNull(pipe.get());
		}

		TEST_METHOD(GetNewPipe_WhenServerHasNotNewClient_ReturnsNull)
		{
			// Arrange
			auto [server, pipeManager] = ConfigureTestPipeManager();

			// Act
			auto pipe = pipeManager->GetNewPipe();

			// Assert
			Assert::IsNull(pipe.get());
		}
	private:
		inline std::tuple<MockServer*, std::unique_ptr<PipeManager>> ConfigureTestPipeManager()
		{
			auto server = new MockServer();
			auto pipe = std::make_unique<PipeManager>(std::unique_ptr<MockServer>(server));

			return std::make_tuple(server, std::move(pipe));
		}
	};
}