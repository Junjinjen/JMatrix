#include "PipeManager.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace services
		{
			namespace task_service
			{
				namespace network_pipeline
				{
					namespace pipe_management
					{
						PipeManager::PipeManager()
							: isStopped_(false)
						{
						}

						PipeManager::~PipeManager()
						{
							Stop();
						}

						bool PipeManager::Initialize()
						{
							if (!server_->Initialize())
							{
								logger_->LogFatal("Unable to initialize pipe manager. Network server initialization failed");
								return false;
							}

							logger_->LogInfo("Pipe manager started");
							return true;
						}

						void PipeManager::Stop()
						{
							if (!isStopped_)
							{
								server_->Stop();
								isStopped_ = true;

								logger_->LogInfo("Pipe manager stopped");
							}
						}

						bool PipeManager::HasNewPipe()
						{
							if (!isStopped_)
							{
								return server_->HasNewClient();
							}

							return false;
						}

						Pipe PipeManager::GetNewPipe()
						{
							JUNJINJEN_ASSERT(HasNewPipe());
							logger_->LogInfo("Creating new pipe");

							return Pipe(server_->GetNewClient());
						}
					}
				}
			}
		}
	}
}
