#include "Task.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace tasking
		{
			Task::Task(std::unique_ptr<Pipe> pipe)
				: pipe_(std::move(pipe))
			{
			}

			bool Task::Completed() const
			{
				return completed_;
			}

			void Task::Stop()
			{
				if (!completed_)
				{
					pipe_->Close();
					completed_ = true;
					logger_->Log("Task completed");
				}
			}
		}
	}
}
