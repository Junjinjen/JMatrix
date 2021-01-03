#pragma once
#include "NetworkPipeline/PipeManagement/Pipe/Pipe.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace network_pipeline
		{
			namespace pipe_management
			{
				using logger::Logger;
				using network::NetworkServer;

				class PipeManager
				{
				public:
					PipeManager(std::shared_ptr<Logger> logger, std::unique_ptr<NetworkServer> server);
					~PipeManager();

					bool Initialize(uint16_t port);
					void Stop();

					bool HasNewPipe();
					std::unique_ptr<Pipe> GetNewPipe();
				private:
					std::shared_ptr<Logger> logger_;
					std::unique_ptr<NetworkServer> server_;
					bool isStopped_;
				};
			}
		}
	}
}