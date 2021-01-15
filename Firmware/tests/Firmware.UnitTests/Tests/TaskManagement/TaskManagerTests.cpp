#include "CppUnitTest.h"
#include "TaskManagement/TaskManager/TaskManager.h"
#include "../../Mocks/Network/Server/MockServer.h"
#include "../../Mocks/Network/Client/MockClient.h"
#include "../../Mocks/Logger/DebugLogger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace junjinjen_matrix::firmware::task_management;

namespace JunjinjenMatrixUnitTests
{
	TEST_CLASS(TaskManagerUnitTests)
	{
	public:
		TEST_METHOD(HasNewTasks_WhenPipeManagerHasNewPipeWithMessage_ReturnsTrue)
		{
			// Arrange
			auto [server, taskManager] = ConfigureTaskManager();
			auto client = new MockClient();
			server->AddClient(client);
			client->AddMessage("New message");

			// Act / Assert
			Assert::IsTrue(taskManager->HasNewTasks());
		}

		TEST_METHOD(HasNewTasks_WhenPipeManagerHasNewPipeWithoutMessage_ReturnsFalse)
		{
			// Arrange
			auto [server, taskManager] = ConfigureTaskManager();
			auto client = new MockClient();
			server->AddClient(client);

			// Act / Assert
			Assert::IsFalse(taskManager->HasNewTasks());
		}

		TEST_METHOD(HasNewTasks_WhenPipeManagerHasNotNewPipe_ReturnsFalse)
		{
			// Arrange
			auto [server, taskManager] = ConfigureTaskManager();

			// Act / Assert
			Assert::IsFalse(taskManager->HasNewTasks());
		}
	private:
		inline std::tuple<MockServer*, std::unique_ptr<TaskManager>> ConfigureTaskManager()
		{
			auto logger = std::make_shared<DebugLogger>();
			auto server = new MockServer();
			auto pipeManager = new PipeManager(logger, std::unique_ptr<MockServer>(server));
			auto taskManager = std::make_unique<TaskManager>(logger, std::unique_ptr<PipeManager>(pipeManager));


			return std::make_tuple(server, std::move(taskManager));
		}
	};
}