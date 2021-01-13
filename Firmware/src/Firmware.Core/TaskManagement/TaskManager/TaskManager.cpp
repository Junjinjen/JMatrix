#include "TaskManager.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace task_management
		{
			TaskManager::TaskManager(std::shared_ptr<Logger> logger, std::unique_ptr<PipeManager> pipeManager)
				: logger_(logger), pipeManager_(std::move(pipeManager)), isStopped_(false)
			{
			}

			TaskManager::~TaskManager()
			{
				Stop();
			}

			bool TaskManager::HasNewTasks()
			{
				while (pipeManager_->HasNewPipe())
				{
					newPipes_.push_back(pipeManager_->GetNewPipe());
				}

				auto it = newPipes_.begin();
				while (it != newPipes_.end())
				{
					if ((*it)->HasNewMessage())
					{
						auto task = TaskFactory::Create(reinterpret_cast<const char*>(&(*it)->GetNewMessage()[0]), logger_, *it);
						newTasks_.push_back(std::move(task));
						it = newPipes_.erase(it);
					}
					else
					{
						it++;
					}
				}

				return !newTasks_.empty();
			}

			std::vector<std::unique_ptr<Task>> TaskManager::GetNewTasks()
			{
				std::vector<std::unique_ptr<Task>> vec;

				if (HasNewTasks())
				{
					for (size_t i = 0; i < newTasks_.size(); i++)
					{
						vec.push_back(std::move(newTasks_[i]));
					}

					newTasks_.clear();
				}

				return vec;
			}

			void TaskManager::Stop()
			{
				if (!isStopped_)
				{
					pipeManager_->Stop();
					isStopped_ = true;
					logger_->Log("Task manager stopped");
				}
			}
		}
	}
}
