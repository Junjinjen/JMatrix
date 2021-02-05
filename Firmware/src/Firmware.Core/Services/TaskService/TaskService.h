#pragma once
#include "Services/Service.h"
#include "Tasking/TaskFactory/TaskFactory.h"
#include "NetworkPipeline/PipeManagement/PipeManager/PipeManager.h"

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

			class TaskService : public Service
			{
			public:
				virtual bool Initialize() override;

				virtual void Update() override;
			private:
				PipeManager pipeManager_;
				std::vector<Task> tasks_;
				std::vector<std::unique_ptr<Pipe>> pipes_;

				inline void CheckForNewTasks();
				inline void CreateTaskFromPipe(const DataContainer& message, std::unique_ptr<Pipe> pipe);
			};
		}
	}
}
