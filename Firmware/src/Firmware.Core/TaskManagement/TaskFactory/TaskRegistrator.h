#pragma once
#include "TaskManagement/TaskFactory/TaskFactory.h"
#define REGISTER_TASK(task) junjinjen_matrix::firmware::task_management::TaskRegistrator<task> __register##task;

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace task_management
		{
			template <typename T>
			class TaskRegistrator
			{
			public:
				TaskRegistrator(void)
				{
					TaskFactory::AddTaskCreator(T::GetTaskName(), [](std::shared_ptr<Logger>& logger, std::unique_ptr<Pipe>& pipe)
						{
							return std::unique_ptr<Task>(new T(logger, std::move(pipe)));
						});
				}
			};
		}
	}
}