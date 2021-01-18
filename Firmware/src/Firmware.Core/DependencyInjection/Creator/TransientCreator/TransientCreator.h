#pragma once
#include "DependencyInjection/Creator/Creator.h"
#include <functional>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace dependency_injection
		{
			namespace creator
			{
				template<typename T>
				class TransientCreator : public Creator
				{
				public:
					void Register()
					{
						creator_ = []() { return new T(); };
					}

					void Register(std::function<T*()> creator)
					{
						creator_ = creator;
					}

					virtual std::shared_ptr<void> Create() override
					{
						return std::static_pointer_cast<void>(std::shared_ptr<T>(creator_()));
					}
				private:
					std::function<T*()> creator_;
				};
			}
		}
	}
}
