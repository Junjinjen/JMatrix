#pragma once
#include "Tasking/TaskFactory/TaskFactory.h"

#define TASK_CLASS(task_name) class task_name;\
junjinjen_matrix::firmware::tasking::TaskRegistrator<task_name> __register##task_name(#task_name);\
class task_name

#define NAMED_TASK_CLASS(task_class_name, task_name) class task_class_name;\
junjinjen_matrix::firmware::tasking::TaskRegistrator<task_class_name> __register##task_class_name(task_name);\
class task_class_name

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace tasking
		{
			template <typename T>
			class TaskRegistrator
			{
			public:
				TaskRegistrator(const std::string& taskName)
				{
					TaskFactory::AddTaskCreator(taskName, [](std::unique_ptr<Pipe>& pipe)
						{
							return std::unique_ptr<Task>(new T(std::move(pipe)));
						});
				}
			};
		}
	}
}