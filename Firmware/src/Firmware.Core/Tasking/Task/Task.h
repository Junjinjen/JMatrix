#pragma once
#include "Logging/Logger.h"
#include "DependencyInjection/Container/Container.h"
#include "Utilities/ByteDefinitions/ByteDefinitions.h"
#include "NetworkPipeline/PipeManagement/Pipe/Pipe.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace tasking
		{
			using logging::Logger;
			using network::pipe_management::Pipe;
			using utilities::byte_definitions::byte_string;

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
				bool completed_;
			};
		}
	}
}