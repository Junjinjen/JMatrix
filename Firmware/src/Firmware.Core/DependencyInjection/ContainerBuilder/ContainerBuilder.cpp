#include "ContainerBuilder.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace dependency_injection
		{
			Container* ContainerBuilder::Build()
			{
				delete Container::instance_;
				Container::instance_ = new Container();
				Container::instance_->creatos_ = std::move(creatos_);
				return Container::instance_;
			}
		}
	}
}
