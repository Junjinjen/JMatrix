#pragma once
#include "DependencyInjection/Creator/Creator.h"
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <memory>

#define INJECT_FIELD(Interface, FieldName)\
std::shared_ptr<Interface> FieldName = junjinjen_matrix::firmware::dependency_injection::Container::GetInstance()->Resolve<Interface>();

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace dependency_injection
		{
			class ContainerBuilder;
			using creator::Creator;

			class Container
			{
				friend class ContainerBuilder;

				Container();
				static Container* instance_;
			public:
				~Container();

				Container(Container&) = delete;
				Container(const Container&) = delete;
				Container(Container&&) = delete;
				void operator=(const Container&) = delete;

				static Container* GetInstance();

				template<typename T>
				std::shared_ptr<T> Resolve() const
				{
					auto element = creatos_.find(typeid(T));
					if (element != creatos_.end())
					{
						return std::static_pointer_cast<T>(element->second->Create());
					}
					
					return nullptr;
				}
			private:
				std::unordered_map<std::type_index, Creator*> creatos_;
			};
		}
	}
}
