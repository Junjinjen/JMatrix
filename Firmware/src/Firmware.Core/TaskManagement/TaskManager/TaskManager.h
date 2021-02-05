#pragma once
#include "DependencyInjection/Container/Container.h"
#include "Logging/Logger.h"
#include "NetworkPipeline/PipeManagement/PipeManager/PipeManager.h"
#include "TaskManagement/Task/Task.h"
#include "TaskManagement/TaskFactory/TaskFactory.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace task_management
		{
			using logging::Logger;
			using network::pipe_management::PipeManager;

			class TaskManager
			{
			public:
				TaskManager(std::unique_ptr<PipeManager> pipeManager);
				~TaskManager();

				bool HasNewTask();
				std::unique_ptr<Task> GetNewTask();

				void Stop();
			private:
				INJECT_FIELD(Logger, logger_)
				std::unique_ptr<PipeManager> pipeManager_;
				bool isStopped_;

				std::queue<std::unique_ptr<Task>> newTasks_;
				std::vector<std::unique_ptr<Pipe>> newPipes_;
			};
		}
	}
}
