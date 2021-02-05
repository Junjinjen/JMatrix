#pragma once
#include "Services/Service.h"
#include "Tasking/TaskFactory/TaskFactory.h"
#include "NetworkPipeline/PipeManagement/PipeManager/PipeManager.h"
#include "Messaging/SystemMessages/InvalidMessageFormat.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace services
		{
			using tasking::Task;
			using network::pipe_management::Pipe;
			using network::pipe_management::PipeManager;
			using messaging::DataContainer;
			using messaging::system_messages::InvalidMessageFormat;
			using tasking::TaskFactory;
			using messaging::Value;
			using logging::Logger;

			class TaskService : public Service
			{
			public:
				virtual bool Initialize() override;

				virtual void Update() override;
			private:
				INJECT_FIELD(Logger, logger_)
				PipeManager pipeManager_;
				std::vector<std::unique_ptr<Task>> tasks_;
				std::vector<std::unique_ptr<Pipe>> pipes_;

				inline void CheckForNewPipes();
				inline bool HandleMessage(DataContainer& message, std::unique_ptr<Pipe>& pipe);
				inline bool StartTask(const DataContainer& message, std::unique_ptr<Pipe>& pipe);
				inline bool ReturnAllTasks(DataContainer& message, std::unique_ptr<Pipe>& pipe);
			};
		}
	}
}
