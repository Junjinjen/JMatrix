#pragma once
#include "TaskManagement/Task/Task.h"
#include "TaskManagement/TaskFactory/TaskRegistrator.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace task_management
		{
			namespace system_tasks
			{
				class InvalidTask : public Task
				{
				public:
					static const std::string GetTaskName()
					{
						return "invalid_task";
					}

					InvalidTask(std::shared_ptr<Logger> logger, std::unique_ptr<Pipe> pipe);

					virtual void Execute() override;
				};

				REGISTER_TASK(InvalidTask)
			}
		}
	}
}
