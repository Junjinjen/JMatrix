#pragma once
#include <memory>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace dependency_injection
		{
			namespace creator
			{
				class Creator
				{
				public:
					virtual std::shared_ptr<void> Create() = 0;
				};
			}
		}
	}
}