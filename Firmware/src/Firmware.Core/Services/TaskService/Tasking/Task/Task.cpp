#include "Task.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace services
		{
			namespace task_service
			{
				namespace tasking
				{
					Task::Task(Pipe& pipe)
						: pipe_(std::move(pipe)), isStopped_(false)
					{
					}

					bool Task::Completed() const
					{
						return isStopped_;
					}

					void Task::Stop()
					{
						if (!isStopped_)
						{
							pipe_.Close();
							isStopped_ = true;

							logger_->LogInfo("Task stopped");
						}
					}
				}
			}
		}
	}
}
