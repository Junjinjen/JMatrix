#include "Core.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		Core::Core()
			: isInitialized_(false)
		{
		}

		void Core::Initialize()
		{
			JUNJINJEN_ASSERT(!isInitialized_);
			for (auto& service : services_)
			{
				JUNJINJEN_ASSERT(service->Initialize());
			}

			isInitialized_ = true;
		}

		void Core::Loop()
		{
			if (isInitialized_)
			{
				for (auto& service : services_)
				{
					service->Update();
				}
			}
		}
	}
}
