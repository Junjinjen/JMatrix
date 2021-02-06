#pragma once
#include "Services/TaskService/NetworkPipeline/PipeManagement/Pipe/Pipe.h"
#include "Services/TaskService/NetworkPipeline/Network/NetworkServer.h"

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
						using network::NetworkServer;

						class PipeManager
						{
						public:
							PipeManager();
							~PipeManager();

							bool Initialize();
							void Stop();

							bool HasNewPipe();
							Pipe GetNewPipe();
						private:
							INJECT_FIELD(Logger, logger_)
							INJECT_FIELD(NetworkServer, server_)
							bool isStopped_;
						};
					}
				}
			}
		}
	}
}
