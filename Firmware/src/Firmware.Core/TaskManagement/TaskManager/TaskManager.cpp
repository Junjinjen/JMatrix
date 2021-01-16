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
						auto json = (*it)->GetNewMessage();
						rapidjson::Document document;
						std::unique_ptr<Task> task;

						if (!document.Parse((const char*)&json[0]).HasParseError())
						{
							if (document.HasMember("task_name"))
							{
								rapidjson::Value& name = document["task_name"];
								if (name.IsString())
								{
									task = TaskFactory::Create(name.GetString(), logger_, *it);
								}
							}
						}

						if (!task)
						{
							task = TaskFactory::Create("invalid_task", logger_, *it);
						}
						
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
