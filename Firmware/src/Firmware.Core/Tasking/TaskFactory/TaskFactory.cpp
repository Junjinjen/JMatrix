#include "TaskFactory.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace tasking
		{
			bool TaskFactory::AddTaskCreator(const std::string& taskName, task_creator_t creator)
			{
				if (GetMap().find(taskName) == GetMap().end())
				{
					GetMap().insert(std::make_pair(taskName, creator));
					return true;
				}

				return false;
			}

			std::unique_ptr<Task> TaskFactory::Create(const std::string& taskName, std::unique_ptr<Pipe>& pipe)
			{
				auto it = GetMap().find(taskName);
				if (it != GetMap().end())
				{
					return it->second(pipe);
				}

				return nullptr;
			}

			inline std::map<std::string, task_creator_t>& TaskFactory::GetMap()
			{
				static std::map<std::string, task_creator_t> factoryMap;
				return factoryMap;
			}
		}
	}
}
