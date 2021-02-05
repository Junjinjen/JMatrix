#include "TaskService.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace services
		{
			inline void TaskService::CheckForNewTasks()
			{
				while (pipeManager_.HasNewPipe())
				{
					pipes_.push_back(pipeManager_.GetNewPipe());
				}

				auto it = pipes_.begin();
				while (it != pipes_.end())
				{
					if (!(*it)->Connected())
					{
						(*it)->Close();
						it = pipes_.erase(it);
					}
					else if ((*it)->HasNewMessage())
					{
						auto message = (*it)->GetNewMessage();
						CreateTaskFromPipe(message, std::move(*it));
						it = pipes_.erase(it);
					}
					else
					{
						it++;
					}
				}
			}
		}
	}
}
