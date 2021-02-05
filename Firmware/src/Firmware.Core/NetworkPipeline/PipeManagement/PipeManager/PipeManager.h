#pragma once
#include "NetworkPipeline/PipeManagement/Pipe/Pipe.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace network
		{
			namespace pipe_management
			{
				using network::NetworkServer;

				class PipeManager
				{
				public:
					PipeManager(std::unique_ptr<NetworkServer> server);
					~PipeManager();

					void Stop();

					bool HasNewPipe();
					std::unique_ptr<Pipe> GetNewPipe();
				private:
					INJECT_FIELD(Logger, logger_)
					std::unique_ptr<NetworkServer> server_;
					bool isStopped_;
				};
			}
		}
	}
}