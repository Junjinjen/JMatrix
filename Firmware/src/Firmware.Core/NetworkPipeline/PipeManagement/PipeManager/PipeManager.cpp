#include "PipeManager.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace network_pipeline
		{
			namespace pipe_management
			{
				PipeManager::PipeManager(std::unique_ptr<NetworkServer> server)
					: server_(std::move(server)), isStopped_(false)
				{
				}

				PipeManager::~PipeManager()
				{
					Stop();
				}

				void PipeManager::Stop()
				{
					if (!isStopped_)
					{
						server_->Stop();
						isStopped_ = true;
						logger_->Log("Pipe manager stopped");
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

				std::unique_ptr<Pipe> PipeManager::GetNewPipe()
				{
					if (HasNewPipe())
					{
						logger_->Log("Creating new pipe");
						return std::unique_ptr<Pipe>(new Pipe(server_->GetNewClient()));
					}

					return nullptr;
				}
			}
		}
	}
}
