#pragma once
#include "Logging/Logger.h"
#include "DependencyInjection/Container/Container.h"
#include "Messaging/DataContainer/DataContainer.h"
#include "Messaging/SystemMessages/InvalidMessageFormat.h"
#include "Messaging/SystemMessages/DeserializationFailed.h"
#include "Messaging/SystemMessages/SerializationFailed.h"
#include "Messaging/Serialization/ContainerSerializer.h"
#include "Services/TaskService/NetworkPipeline/PipeManagement/PipeManager/PipeManager.h"
#include "Services/TaskService/Tasking/TaskFactory/TaskFactory.h"
#include "Services/Service.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace services
		{
			namespace task_service
			{
				using logging::Logger;
				using messaging::DataContainer;
				using messaging::Value;
				using messaging::system_messages::DeserializationFailed;
				using messaging::system_messages::SerializationFailed;
				using messaging::system_messages::InvalidMessageFormat;
				using messaging::serialization::ContainerSerializer;
				using network_pipeline::pipe_management::PipeManager;
				using network_pipeline::pipe_management::Pipe;
				using tasking::Task;
				using tasking::TaskFactory;

				class TaskService : public Service
				{
				public:
					TaskService();
					~TaskService();

					virtual bool Initialize() override;
					virtual void Update() override;

					virtual void Stop() override;
				private:
					INJECT_FIELD(Logger, logger_)
					PipeManager pipeManager_;
					std::vector<std::unique_ptr<Task>> tasks_;
					std::vector<Pipe> pipes_;
					bool isStopped_;

					inline void CheckForNewPipes();
					inline bool HandleMessage(DataContainer& message, Pipe& pipe);
				};
			}

			using task_service::TaskService;
		}
	}
}
