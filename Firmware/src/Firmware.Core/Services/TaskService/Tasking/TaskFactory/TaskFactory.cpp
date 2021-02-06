#include "TaskFactory.h"

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
					bool TaskFactory::AddTaskCreator(const std::string& taskName, task_creator_t creator)
					{
						if (Map().find(taskName) == Map().end())
						{
							Map().insert(std::make_pair(taskName, creator));
							return true;
						}

						return false;
					}

					std::unique_ptr<Task> TaskFactory::Create(const std::string& taskName, Pipe& pipe)
					{
						auto it = Map().find(taskName);
						if (it != Map().end())
						{
							return it->second(std::move(pipe));
						}

						return nullptr;
					}

					const std::map<std::string, task_creator_t>& TaskFactory::GetMap()
					{
						return Map();
					}

					std::map<std::string, task_creator_t>& TaskFactory::Map()
					{
						static std::map<std::string, task_creator_t> factoryMap;
						return factoryMap;
					}
				}
			}
		}
	}
}
