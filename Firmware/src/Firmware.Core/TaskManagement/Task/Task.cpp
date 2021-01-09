#include "Task.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace task_management
		{
			Task::Task(std::shared_ptr<Logger> logger, std::unique_ptr<Pipe> pipe)
				: logger_(logger), pipe_(std::move(pipe)), isStopped_(false)
			{
			}

			Task::~Task()
			{
				Stop();
			}

			bool Task::IsStopped() const
			{
				return isStopped_;
			}

			void Task::Stop()
			{
				if (!isStopped_)
				{
					pipe_->Close();
					logger_->Log("Task stopped");
				}
			}
		}
	}
}
