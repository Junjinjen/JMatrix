#include "PipeManager.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace network_pipeline
		{
			namespace pipe_management
			{
				PipeManager::PipeManager(std::shared_ptr<Logger> logger, std::unique_ptr<NetworkServer> server)
					: logger_(logger), server_(std::move(server)), isStopped_(false)
				{
				}

				PipeManager::~PipeManager()
				{
					Stop();
				}

				bool PipeManager::Initialize(uint16_t port)
				{
					logger_->Log("Initializing pipe manager");

					if (!server_->Initialize(port))
					{
						logger_->Log("Unable to initialize pipe manager: Server initialization error");
						return false;
					}

					isStopped_ = false;
					return true;
				}

				void PipeManager::Stop()
				{
					if (!isStopped_)
					{
						logger_->Log("Stopping pipe manager");
						server_->Stop();
					}
				}

				bool PipeManager::HasNewPipe()
				{
					if (isStopped_)
					{
						return false;
					}

					return server_->HasNewClient();
				}

				std::unique_ptr<Pipe> PipeManager::GetNewPipe()
				{
					if (HasNewPipe())
					{
						logger_->Log("Creating new pipe");
						return std::unique_ptr<Pipe>(new Pipe(logger_, server_->GetNewClient()));
					}

					return nullptr;
				}
			}
		}
	}
}
