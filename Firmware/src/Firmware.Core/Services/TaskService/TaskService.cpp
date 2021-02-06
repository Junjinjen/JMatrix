#include "TaskService.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace services
		{
			namespace task_service
			{
				bool TaskService::Initialize()
				{
					if (!pipeManager_.Initialize())
					{
						logger_->LogFatal("Unable to initialize task service. Pipe manager initialization failed");
						return false;
					}

					logger_->LogInfo("Task service started");
					return true;
				}

				void TaskService::Update()
				{
					CheckForNewPipes();

					auto it = tasks_.begin();
					while (it != tasks_.end())
					{
						(*it)->Execute();
						if ((*it)->Completed())
						{
							it = tasks_.erase(it);
						}
					}
				}

				inline void TaskService::CheckForNewPipes()
				{
					while (pipeManager_.HasNewPipe())
					{
						pipes_.push_back(pipeManager_.GetNewPipe());
					}

					auto it = pipes_.begin();
					while (it != pipes_.end())
					{
						if (!it->Connected())
						{
							it->Close();
							it = pipes_.erase(it);
						}
						else if (it->HasNewMessage())
						{
							auto message = it->GetNewMessage();
							if (!HandleMessage(message, *it))
							{
								it->Close();
							}

							it = pipes_.erase(it);
						}
						else
						{
							it++;
						}
					}
				}

				inline bool TaskService::HandleMessage(DataContainer& message, Pipe& pipe)
				{
					logger_->LogInfo("Handling new message");

					if (!message.HasValue("action"))
					{
						logger_->LogError("The message has not \"action\" member");
						pipe.SendMessage(InvalidMessageFormat());
						return false;
					}

					auto& actionValue = message.GetValue("action");
					if (!actionValue.IsString())
					{
						logger_->LogError("Message \"action\" member is not a string");
						pipe.SendMessage(InvalidMessageFormat());
						return false;
					}

					auto& action = actionValue.AsString();
					if (action == "start_task")
					{
						return StartTask(message, pipe);
					}
					else if (action == "get_all_tasks")
					{
						return ReturnAllTasks(message, pipe);
					}
					else
					{
						logger_->LogError("Action [" + action + "] was not found");
						pipe.SendMessage(InvalidMessageFormat("Action [" + action + "] was not found"));
						return false;
					}
				}

				inline bool TaskService::StartTask(const DataContainer& message, Pipe& pipe)
				{
					logger_->LogInfo("Starting new task");

					if (!message.HasValue("task_name"))
					{
						logger_->LogError("The message has not \"task_name\" member");
						pipe.SendMessage(InvalidMessageFormat());
						return false;
					}

					auto& taskNameValue = message.GetValue("task_name");
					if (!taskNameValue.IsString())
					{
						logger_->LogError("Message \"task_name\" member is not a string");
						pipe.SendMessage(InvalidMessageFormat());
						return false;
					}

					auto& taskName = taskNameValue.AsString();
					auto task = TaskFactory::Create(taskName, pipe);
					if (!task)
					{
						logger_->LogError("Task [" + taskName + "] was not found");
						pipe.SendMessage(InvalidMessageFormat("Invalid task name"));
						return false;
					}

					tasks_.push_back(std::move(task));
					return true;
				}

				inline bool TaskService::ReturnAllTasks(DataContainer& message, Pipe& pipe)
				{
					logger_->LogInfo("Returning all available tasks");

					message.Clear();
					message.SetBoolean("success", true);
					auto& tasks = message.SetArray("tasks");
					for (auto& taskPair : TaskFactory::GetMap())
					{
						tasks.push_back(Value(taskPair.first));
					}

					pipe.SendMessage(message);
					return true;
				}
			}
		}
	}
}
