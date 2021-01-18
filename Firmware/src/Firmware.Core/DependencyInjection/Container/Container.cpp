#include "Container.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace dependency_injection
		{
			Container* Container::instance_ = nullptr;

			Container::Container()
			{
			}

			Container::~Container()
			{
				for (auto it = creatos_.begin(); it != creatos_.end(); it++)
				{
					delete it->second;
				}
			}

			Container* Container::GetInstance()
			{
				return Container::instance_;
			}
		}
	}
}
