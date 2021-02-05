#include "TaskManager.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace task_management
		{
			TaskManager::TaskManager(std::unique_ptr<PipeManager> pipeManager)
				: pipeManager_(std::move(pipeManager)), isStopped_(false)
			{
			}

			TaskManager::~TaskManager()
			{
				Stop();
			}

			bool TaskManager::HasNewTask()
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
						auto pipePtr = it->get();
						auto taskName = pipePtr->GetNewMessage();
						auto task = TaskFactory::Create(reinterpret_cast<const char*>(&taskName[0]), *it);

						/*if (task)
						{
							code = StatusCode::Success;
							newTasks_.push(std::move(task));
						}
						else
						{
							code = StatusCode::TaskNotFound;
						}

						pipePtr->SendMessage(byte_string((const uint8_t*)&code, sizeof(StatusCode)));
						it = newPipes_.erase(it);*/
					}
					else
					{
						it++;
					}
				}

				return !newTasks_.empty();
			}

			std::unique_ptr<Task> TaskManager::GetNewTask()
			{
				if (HasNewTask())
				{
					std::unique_ptr<Task> task = std::move(newTasks_.front());
					newTasks_.pop();
					return task;
				}

				return nullptr;
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
