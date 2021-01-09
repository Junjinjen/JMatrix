#pragma once
#include "Logger/Logger.h"
#include "NetworkPipeline/PipeManagement/PipeManager/PipeManager.h"
#include "TaskManagement/Task/Task.h"
#include "TaskManagement/TaskFactory/TaskFactory.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace task_management
		{
			using logger::Logger;
			using network_pipeline::pipe_management::PipeManager;

			class TaskManager
			{
			public:
				TaskManager(std::shared_ptr<Logger> logger, std::unique_ptr<PipeManager> pipeManager);
				~TaskManager();

				bool HasNewTasks();
				std::vector<std::unique_ptr<Task>> GetNewTasks();

				void Stop();
			private:
				std::shared_ptr<Logger> logger_;
				std::unique_ptr<PipeManager> pipeManager_;

				bool isStopped_;

				std::vector<std::unique_ptr<Task>> newTasks_;
				std::vector<std::unique_ptr<Pipe>> newPipes_;
			};
		}
	}
}
