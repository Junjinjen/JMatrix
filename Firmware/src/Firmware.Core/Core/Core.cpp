#include "Core.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		Core::Core()
			: isStopped_(false), isInitialized_(false)
		{
		}

		Core::~Core()
		{
			Stop();
		}

		bool Core::Initialize()
		{
			for (auto& service : services_)
			{
				if (!service->Initialize())
				{
					return false;
				}
			}

			isInitialized_ = true;
			return true;
		}

		void Core::Stop()
		{
			if (!isStopped_)
			{
				for (auto& service : services_)
				{
					service->Stop();
				}

				isStopped_ = true;
			}
		}

		void Core::Loop()
		{
			for (auto& service : services_)
			{
				service->Update();
			}
		}
	}
}
