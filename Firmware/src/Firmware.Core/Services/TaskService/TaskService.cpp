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

					auto& action = actionValue.AsString();
					auto task = TaskFactory::Create(action, pipe);
					if (!task)
					{
						logger_->LogError("Action [" + action + "] was not found");
						pipe.SendMessage(InvalidMessageFormat("Action [" + action + "] was not found"));
						return false;
					}

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
