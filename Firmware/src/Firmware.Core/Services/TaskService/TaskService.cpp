#include "TaskService.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace services
		{
			namespace task_service
			{
				TaskService::TaskService()
					: isStopped_(false)
				{
				}

				TaskService::~TaskService()
				{
					Stop();
				}

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
							if (!StartTask(message, *it))
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

				inline bool TaskService::StartTask(DataContainer& message, Pipe& pipe)
				{
					logger_->LogInfo("Starting new task");

					if (!message.HasValue("action"))
					{
						logger_->LogError("The message doesn't have an \"action\" member");
						pipe.SendMessage(InvalidMessageFormat("The message doesn't have an \"action\" member"));
						return false;
					}

					auto& actionValue = message.GetValue("action");
					if (!actionValue.IsString())
					{
						logger_->LogError("Message \"action\" member is not a string");
						pipe.SendMessage(InvalidMessageFormat("Message \"action\" member is not a string"));
						return false;
					}

					DataContainer arguments;
					auto& action = actionValue.AsString();
					if (message.HasValue("arguments"))
					{
						auto& argsValue = message.GetValue("arguments");
						if (argsValue.IsContainer())
						{
							arguments = std::move(argsValue.AsContainer());
						}
						else
						{
							logger_->LogWarning("Message contains \"arguments\", but it has wrong format");
						}
					}

					auto task = TaskFactory::Create(action, pipe, arguments);
					if (!task)
					{
						logger_->LogError("Action [" + action + "] was not found");
						pipe.SendMessage(InvalidMessageFormat("Action [" + action + "] was not found"));
						return false;
					}

					tasks_.push_back(std::move(task));
					return true;
				}

				void TaskService::Stop()
				{
					if (!isStopped_)
					{
						pipeManager_.Stop();
						isStopped_ = true;

						logger_->LogInfo("Task service stopped");
					}
				}
			}
		}
	}
}
