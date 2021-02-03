#include "CppUnitTest.h"
#include "DependencyInjection/ContainerBuilder/ContainerBuilder.h"
#include "TaskManagement/TaskManager/TaskManager.h"
#include "../../Mocks/Network/Server/MockServer.h"
#include "../../Mocks/Network/Client/MockClient.h"
#include "../../Mocks/Logger/DebugLogger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace junjinjen_matrix::firmware::task_management;
using namespace junjinjen_matrix::firmware::dependency_injection;

namespace TaskManagementUnitTests
{
	class TestTask : public Task
	{
	public:
		TestTask(std::unique_ptr<Pipe> pipe)
			: Task(std::move(pipe))
		{
		}

		virtual void Execute() override
		{
		}
	};

	TEST_CLASS(TaskManagerUnitTests)
	{
	public:
		TEST_CLASS_INITIALIZE(InitializeIocContainer)
		{
			ContainerBuilder builder;
			builder.AddSingleton<DebugLogger, junjinjen_matrix::firmware::logger::Logger>();
			builder.Build();

			TaskFactory::AddTaskCreator("Test task name", [](std::unique_ptr<Pipe>& pipe)
				{
					return std::unique_ptr<Task>(new TestTask(std::move(pipe)));
				});
		}

		TEST_METHOD(HasNewTasks_WhenPipeManagerHasNewPipeWithMessage_ReturnsTrue)
		{
			// Arrange
			auto [server, taskManager] = ConfigureTaskManager();
			auto client = new MockClient();
			server->AddClient(client);
			client->AddMessage("Test task name");

			// Act / Assert
			Assert::IsTrue(taskManager->HasNewTask());
		}

		TEST_METHOD(HasNewTasks_WhenPipeManagerHasNewPipeWithoutMessage_ReturnsFalse)
		{
			// Arrange
			auto [server, taskManager] = ConfigureTaskManager();
			auto client = new MockClient();
			server->AddClient(client);

			// Act / Assert
			Assert::IsFalse(taskManager->HasNewTask());
		}

		TEST_METHOD(HasNewTasks_WhenPipeManagerHasNotNewPipe_ReturnsFalse)
		{
			// Arrange
			auto [server, taskManager] = ConfigureTaskManager();

			// Act / Assert
			Assert::IsFalse(taskManager->HasNewTask());
		}
	private:
		inline std::tuple<MockServer*, std::unique_ptr<TaskManager>> ConfigureTaskManager()
		{
			auto server = new MockServer();
			auto pipeManager = new PipeManager(std::unique_ptr<MockServer>(server));
			auto taskManager = std::make_unique<TaskManager>(std::unique_ptr<PipeManager>(pipeManager));


			return std::make_tuple(server, std::move(taskManager));
		}
	};
}