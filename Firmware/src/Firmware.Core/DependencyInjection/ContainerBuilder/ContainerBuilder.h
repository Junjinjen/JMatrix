#pragma once
#include "DependencyInjection/Container/Container.h"
#include "DependencyInjection/Creator/SingletonCreator/SingletonCreator.h"
#include "DependencyInjection/Creator/TransientCreator/TransientCreator.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace dependency_injection
		{
			using creator::SingletonCreator;
			using creator::TransientCreator;

			class ContainerBuilder
			{
			public:
				Container* Build();

				template<typename Service, typename Interface>
				void AddSingleton()
				{
					static_assert(std::is_base_of<Interface, Service>::value, "Service should inherit Interface");
					auto creator = new SingletonCreator<Service>();
					creator->Register();
					creatos_.insert(std::pair<std::type_index, Creator*>(typeid(Interface), creator));
				}

				template<typename Service>
				void AddSingleton()
				{
					auto creator = new SingletonCreator<Service>();
					creator->Register();
					creatos_.insert(std::pair<std::type_index, Creator*>(typeid(Service), creator));
				}

				template<typename Service, typename Interface>
				void AddSingleton(Service* item)
				{
					static_assert(std::is_base_of<Interface, Service>::value, "Service should inherit Interface");
					auto creator = new SingletonCreator<Service>();
					creator->Register(item);
					creatos_.insert(std::pair<std::type_index, Creator*>(typeid(Interface), creator));
				}

				template<typename Service>
				void AddSingleton(Service* item)
				{
					auto creator = new SingletonCreator<Service>();
					creator->Register(item);
					creatos_.insert(std::pair<std::type_index, Creator*>(typeid(Service), creator));
				}

				template<typename Service, typename Interface>
				void AddSingleton(std::function<Service*()> creator)
				{
					static_assert(std::is_base_of<Interface, Service>::value, "Service should inherit Interface");
					auto creatorObj = new SingletonCreator<Service>();
					creatorObj->Register(creator);
					creatos_.insert(std::pair<std::type_index, Creator*>(typeid(Interface), creatorObj));
				}

				template<typename Service>
				void AddSingleton(std::function<Service*()> creator)
				{
					auto creatorObj = new SingletonCreator<Service>();
					creatorObj->Register(creator);
					creatos_.insert(std::pair<std::type_index, Creator*>(typeid(Service), creatorObj));
				}

				template<typename Service, typename Interface>
				void AddTransient()
				{
					static_assert(std::is_base_of<Interface, Service>::value, "Service should inherit Interface");
					auto creator = new TransientCreator<Service>();
					creator->Register();
					creatos_.insert(std::pair<std::type_index, Creator*>(typeid(Interface), creator));
				}

				template<typename Service>
				void AddTransient()
				{
					auto creator = new TransientCreator<Service>();
					creator->Register();
					creatos_.insert(std::pair<std::type_index, Creator*>(typeid(Service), creator));
				}

				template<typename Service, typename Interface>
				void AddTransient(std::function<Service*()> creator)
				{
					static_assert(std::is_base_of<Interface, Service>::value, "Service should inherit Interface");
					auto creatorObj = new TransientCreator<Service>();
					creatorObj->Register(creator);
					creatos_.insert(std::pair<std::type_index, Creator*>(typeid(Interface), creatorObj));
				}

				template<typename Service>
				void AddTransient(std::function<Service*()> creator)
				{
					auto creatorObj = new TransientCreator<Service>();
					creatorObj->Register(creator);
					creatos_.insert(std::pair<std::type_index, Creator*>(typeid(Service), creatorObj));
				}
			private:
				std::unordered_map<std::type_index, Creator*> creatos_;
			};
		}
	}
}
