#pragma once
#include "Services/TaskService/Tasking/Task/Task.h"
#include <functional>
#include <map>

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
					using task_creator_t = std::function<std::unique_ptr<Task>(Pipe&& pipe)>;

					class TaskFactory
					{
					public:
						static bool AddTaskCreator(const std::string& taskName, task_creator_t creator);

						static std::unique_ptr<Task> Create(const std::string& taskName, Pipe& pipe);
						static const std::map<std::string, task_creator_t>& GetMap();
					private:
						static std::map<std::string, task_creator_t>& Map();
					};
				}
			}
		}
	}
}
