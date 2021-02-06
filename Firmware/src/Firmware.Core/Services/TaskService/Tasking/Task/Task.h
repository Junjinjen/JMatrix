#pragma once
#include "Logging/Logger.h"
#include "DependencyInjection/Container/Container.h"
#include "Services/TaskService/NetworkPipeline/PipeManagement/Pipe/Pipe.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace services
		{
			namespace task_service
			{
				namespace tasking
				{
					using logging::Logger;
					using network_pipeline::pipe_management::Pipe;

					class Task
					{
					public:
						Task(Pipe pipe);
						virtual ~Task() = default;

						bool Completed() const;
						void Stop();

						virtual void Execute() = 0;
					protected:
						INJECT_FIELD(Logger, logger_)
						Pipe pipe_;
					private:
						bool isStopped_;
					};
				}
			}
		}
	}
}
