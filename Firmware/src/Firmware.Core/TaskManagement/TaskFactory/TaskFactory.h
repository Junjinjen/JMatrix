#pragma once
#include "TaskManagement/Task/Task.h"
#include <map>
#include <functional>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace task_management
		{
			using task_creator_t = std::function<std::unique_ptr<Task>(std::shared_ptr<Logger>& logger, std::unique_ptr<Pipe>& pipe)>;

			class TaskFactory
			{
			public:
				static bool AddTaskCreator(const std::string& taskName, task_creator_t creator);

				static std::unique_ptr<Task> Create(const std::string& taskName, std::shared_ptr<Logger>& logger, std::unique_ptr<Pipe>& pipe);
			private:
				inline static std::map<std::string, task_creator_t>& GetMap();
				inline static std::unique_ptr<Task> CreateInvalidTask(std::shared_ptr<Logger>& logger, std::unique_ptr<Pipe>& pipe);
			};
		}
	}
}