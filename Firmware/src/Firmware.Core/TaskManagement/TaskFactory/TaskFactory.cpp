#include "TaskFactory.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace task_management
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

			std::unique_ptr<Task> TaskFactory::Create(const std::string& taskName, std::shared_ptr<Logger>& logger, std::unique_ptr<Pipe>& pipe)
			{
				auto it = GetMap().find(taskName);
				if (it != GetMap().end())
				{
					return it->second(logger, pipe);
				}

				return CreateInvalidTask(logger, pipe);
			}

			inline std::map<std::string, task_creator_t>& TaskFactory::GetMap()
			{
				static std::map<std::string, task_creator_t> factoryMap;
				return factoryMap;
			}

			inline std::unique_ptr<Task> TaskFactory::CreateInvalidTask(std::shared_ptr<Logger>& logger, std::unique_ptr<Pipe>& pipe)
			{
				auto it = GetMap().find("invalid_task");
				if (it != GetMap().end())
				{
					return it->second(logger, pipe);
				}

				return nullptr;
			}
		}
	}
}
