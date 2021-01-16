#pragma once
#include "TaskManagement/Task/Task.h"
#include "TaskManagement/TaskFactory/TaskRegistrator.h"
#include "Utilities/ByteDefinitions/ByteDefinitions.h"
#include "rapidjson/document.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace task_management
		{
			namespace system_tasks
			{
				using utilities::byte_definitions::byte_string_buffer;

				class InvalidTask : public Task
				{
				public:
					static const std::string GetTaskName()
					{
						return "invalid_task";
					}

					InvalidTask(std::shared_ptr<Logger> logger, std::unique_ptr<Pipe> pipe);

					virtual void Execute() override;
				};

				REGISTER_TASK(InvalidTask)
			}
		}
	}
}
