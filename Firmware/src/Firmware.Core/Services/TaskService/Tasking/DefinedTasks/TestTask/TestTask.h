#pragma once
#include "Services/TaskService/Tasking/TaskFactory/TaskRegistrator.h"
#include "Messaging/SystemMessages/StatusResult.h"

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
						using messaging::system_messages::StatusResult;

						class TestTask : public Task
						{
						public:
							TestTask(Pipe& pipe);

							virtual void Execute() override;
						};

						REGISTER_TASK(TestTask);
					}
				}
			}
		}
	}
}
