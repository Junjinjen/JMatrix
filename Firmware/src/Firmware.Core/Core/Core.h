#pragma once
#include "Utilities/Assertion/AssertDefinition.h"
#include "Services/Service.h"
#include <vector>
#include <memory>

namespace junjinjen_matrix
{
	namespace firmware
	{
		using services::Service;

		class Core
		{
		public:
			Core();
			~Core();

			template<typename T>
			void AddService(std::shared_ptr<T> service)
			{
				AddService(service.get());
			}

			template<typename T>
			void AddService(T* service)
			{
				JUNJINJEN_ASSERT(!isInitialized_);
				services_.push_back(service);
			}

			bool Initialize();
			void Stop();

			void Loop();
		private:
			std::vector<Service*> services_;
			bool isInitialized_;
			bool isStopped_;
		};
	}
}
