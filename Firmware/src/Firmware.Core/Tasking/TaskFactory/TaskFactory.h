#pragma once
#include "Tasking/Task/Task.h"
#include <map>
#include <functional>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace tasking
		{
			using task_creator_t = std::function<std::unique_ptr<Task>(std::unique_ptr<Pipe>& pipe)>;

			class TaskFactory
			{
			public:
				static bool AddTaskCreator(const std::string& taskName, task_creator_t creator);

				static std::unique_ptr<Task> Create(const std::string& taskName, std::unique_ptr<Pipe>& pipe);
				static const std::map<std::string, task_creator_t>& GetMap();
			private:
				static std::map<std::string, task_creator_t>& Map();
			};
		}
	}
}