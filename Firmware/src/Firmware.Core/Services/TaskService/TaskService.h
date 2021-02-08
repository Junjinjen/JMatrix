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

				/// <summary>
				/// Service that provides executing tasks over the network.
				/// <para>Incoming <see cref="DataContainer"/> format:</para>
				/// <para>– Key "action": task name (<see cref="std::string"/>);</para>
				///	<para>– Key "arguments": an optional argument that contains additional task executing parameters (<see cref="DataContainer"/>).</para>
				/// <para>Depends on the next interfaces (must be registered in IoC):</para>
				/// <para>– <see cref="Logger"/>;</para>
				/// <para>– <see cref="NetworkServer"/>;</para>
				/// <para>– <see cref="ContainerSerializer"/>.</para>
				/// </summary>
				class TaskService : private Service
				{
				public:
					TaskService();
					~TaskService();
				private:
					virtual void Update() override;
					virtual bool Initialize() override;

					INJECT_FIELD(Logger, logger_)
					PipeManager pipeManager_;
					std::vector<std::unique_ptr<Task>> tasks_;
					std::vector<Pipe> pipes_;
					bool isInitialized_;

					inline void CheckForNewPipes();
					inline bool StartTask(DataContainer& message, Pipe& pipe);
				};
			}

			using task_service::TaskService;
		}
	}
}
