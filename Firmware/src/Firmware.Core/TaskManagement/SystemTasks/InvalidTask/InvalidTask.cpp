#include "InvalidTask.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace task_management
		{
			namespace system_tasks
			{
				InvalidTask::InvalidTask(std::shared_ptr<Logger> logger, std::unique_ptr<Pipe> pipe)
					: Task(logger, std::move(pipe))
				{
				}

				void InvalidTask::Execute()
				{
					rapidjson::Document document;
					document.SetObject();

					rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
					document.AddMember("success", false, allocator);
					document.AddMember("message", "Invalid task name", allocator);

					byte_string_buffer stringBuffer;
					rapidjson::Writer<byte_string_buffer> writer(stringBuffer);
					document.Accept(writer);

					pipe_->SendMessage(stringBuffer.GetString());
					Stop();
				}
			}
		}
	}
}
