#pragma once
#include "Logger/Logger.h"
#include "NetworkPipeline/PipeManagement/Pipe/Pipe.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace task_management
		{
			using logger::Logger;
			using network_pipeline::pipe_management::Pipe;
			using byte_string = std::basic_string<uint8_t>;

			class Task
			{
			public:
				Task(std::shared_ptr<Logger> logger, std::unique_ptr<Pipe> pipe);
				virtual ~Task();

				bool IsStopped() const;
				virtual void Stop();

				virtual void Execute() = 0;
			protected:
				std::shared_ptr<Logger> logger_;
				std::unique_ptr<Pipe> pipe_;
			private:
				bool isStopped_;
			};
		}
	}
}