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
				class SingletonCreator : public Creator
				{
				public:
					void Register()
					{
						creator_ = []() { return new T(); };
					}

					void Register(T* item)
					{
						item_ = std::shared_ptr<T>(item);
					}

					void Register(std::function<T*()> creator)
					{
						creator_ = creator;
					}

					virtual std::shared_ptr<void> Create() override
					{
						if (!item_)
						{
							item_ = std::shared_ptr<T>(creator_());
						}

						return std::static_pointer_cast<void>(item_);
					}
				private:
					std::function<T*()> creator_;
					std::shared_ptr<T> item_;
				};
			}
		}
	}
}
