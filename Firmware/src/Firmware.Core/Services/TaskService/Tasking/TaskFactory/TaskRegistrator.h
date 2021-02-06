#pragma once
#include "Services/TaskService/Tasking/TaskFactory/TaskFactory.h"

#define REGISTER_TASK(task_name) junjinjen_matrix::firmware::services::task_service::tasking::TaskRegistrator<task_name> __register##task_name(#task_name)
#define REGISTER_TASK_WITH_NAME(task_class, task_name) junjinjen_matrix::firmware::services::task_service::tasking::TaskRegistrator<task_class> __register##task_class(task_name)

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
					template <typename T>
					class TaskRegistrator
					{
					public:
						TaskRegistrator(const std::string& taskName)
						{
							TaskFactory::AddTaskCreator(taskName, [](Pipe& pipe)
								{
									return std::unique_ptr<Task>(new T(pipe));
								});
						}
					};
				}
			}
		}
	}
}
