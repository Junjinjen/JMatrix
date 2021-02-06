#include "TestTask.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace services
		{
			namespace task_service
			{
				namespace tasking
				{
					namespace defined_tasks
					{
						TestTask::TestTask(Pipe& pipe)
							: Task(pipe)
						{
						}

						void TestTask::Execute()
						{
							logger_->LogInfo("Sending message from test task");
							pipe_.SendMessage(StatusResult(true, "Hello world!"));
							Stop();
						}
					}
				}
			}
		}
	}
}
