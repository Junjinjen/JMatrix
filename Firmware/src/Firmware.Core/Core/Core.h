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

			template<typename T>
			void RegisterService(std::shared_ptr<T> service)
			{
				JUNJINJEN_ASSERT(!isInitialized_);
				services_.push_back(service);
			}

			template<typename T>
			void RegisterService(T* service)
			{
				RegisterService(std::shared_ptr<Service>(service));
			}

			void Initialize();
			void Loop();
		private:
			std::vector<std::shared_ptr<Service>> services_;
			bool isInitialized_;
		};
	}
}
