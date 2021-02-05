#pragma once
#include "DependencyInjection/Container/Container.h"
#include "Logging/Logger.h"
#include "Utilities/ByteDefinitions/ByteDefinitions.h"
#include "NetworkPipeline/PipeManagement/Pipe/Pipe.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace task_management
		{
			using logging::Logger;
			using network::pipe_management::Pipe;
			using utilities::byte_definitions::byte_string;

			class Task
			{
			public:
				Task(std::unique_ptr<Pipe> pipe);
				virtual ~Task() = default;

				bool Completed() const;
				void Stop();

				virtual void Execute() = 0;
			protected:
				INJECT_FIELD(Logger, logger_)
				std::unique_ptr<Pipe> pipe_;
			private:
				bool completed_;
			};
		}
	}
}