#include "InvalidTask.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace task_management
		{
			namespace system_tasks
			{
				InvalidTask::InvalidTask(std::shared_ptr<Logger> logger, std::unique_ptr<Pipe> pipe)
					: Task(logger, std::move(pipe))
				{
				}

				void InvalidTask::Execute()
				{
					pipe_->SendMessage("Invalid task name");
				}
			}
		}
	}
}
