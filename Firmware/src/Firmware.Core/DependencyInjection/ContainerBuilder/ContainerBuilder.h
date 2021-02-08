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
					auto result = creatos_.insert(std::pair<TypeInfo, Creator*>(GET_TYPE_INFO(Interface), creator));
					JUNJINJEN_ASSERT(result.second);
				}

				template<typename Service>
				void AddSingleton()
				{
					auto creator = new SingletonCreator<Service>();
					creator->Register();
					auto result = creatos_.insert(std::pair<TypeInfo, Creator*>(GET_TYPE_INFO(Service), creator));
					JUNJINJEN_ASSERT(result.second);
				}

				template<typename Service, typename Interface>
				void AddSingleton(Service* item)
				{
					static_assert(std::is_base_of<Interface, Service>::value, "Service should inherit Interface");
					auto creator = new SingletonCreator<Service>();
					creator->Register(item);
					auto result = creatos_.insert(std::pair<TypeInfo, Creator*>(GET_TYPE_INFO(Interface), creator));
					JUNJINJEN_ASSERT(result.second);
				}

				template<typename Service, typename Interface>
				void AddSingleton(std::shared_ptr<Service> item)
				{
					static_assert(std::is_base_of<Interface, Service>::value, "Service should inherit Interface");
					auto creator = new SingletonCreator<Service>();
					creator->Register(item);
					auto result = creatos_.insert(std::pair<TypeInfo, Creator*>(GET_TYPE_INFO(Interface), creator));
					JUNJINJEN_ASSERT(result.second);
				}

				template<typename Service>
				void AddSingleton(Service* item)
				{
					auto creator = new SingletonCreator<Service>();
					creator->Register(item);
					auto result = creatos_.insert(std::pair<TypeInfo, Creator*>(GET_TYPE_INFO(Service), creator));
					JUNJINJEN_ASSERT(result.second);
				}

				template<typename Service>
				void AddSingleton(std::shared_ptr<Service> item)
				{
					auto creator = new SingletonCreator<Service>();
					creator->Register(item);
					auto result = creatos_.insert(std::pair<TypeInfo, Creator*>(GET_TYPE_INFO(Service), creator));
					JUNJINJEN_ASSERT(result.second);
				}

				template<typename Service, typename Interface>
				void AddSingleton(std::function<Service*()> creator)
				{
					static_assert(std::is_base_of<Interface, Service>::value, "Service should inherit Interface");
					auto creatorObj = new SingletonCreator<Service>();
					creatorObj->Register(creator);
					auto result = creatos_.insert(std::pair<TypeInfo, Creator*>(GET_TYPE_INFO(Interface), creatorObj));
					JUNJINJEN_ASSERT(result.second);
				}

				template<typename Service, typename Interface>
				void AddSingleton(std::function<std::shared_ptr<Service>()> creator)
				{
					static_assert(std::is_base_of<Interface, Service>::value, "Service should inherit Interface");
					auto creatorObj = new SingletonCreator<Service>();
					creatorObj->Register(creator);
					auto result = creatos_.insert(std::pair<TypeInfo, Creator*>(GET_TYPE_INFO(Interface), creatorObj));
					JUNJINJEN_ASSERT(result.second);
				}

				template<typename Service>
				void AddSingleton(std::function<Service*()> creator)
				{
					auto creatorObj = new SingletonCreator<Service>();
					creatorObj->Register(creator);
					auto result = creatos_.insert(std::pair<TypeInfo, Creator*>(GET_TYPE_INFO(Service), creatorObj));
					JUNJINJEN_ASSERT(result.second);
				}

				template<typename Service>
				void AddSingleton(std::function<std::shared_ptr<Service>()> creator)
				{
					auto creatorObj = new SingletonCreator<Service>();
					creatorObj->Register(creator);
					auto result = creatos_.insert(std::pair<TypeInfo, Creator*>(GET_TYPE_INFO(Service), creatorObj));
					JUNJINJEN_ASSERT(result.second);
				}

				template<typename Service, typename Interface>
				void AddTransient()
				{
					static_assert(std::is_base_of<Interface, Service>::value, "Service should inherit Interface");
					auto creator = new TransientCreator<Service>();
					creator->Register();
					auto result = creatos_.insert(std::pair<TypeInfo, Creator*>(GET_TYPE_INFO(Interface), creator));
					JUNJINJEN_ASSERT(result.second);
				}

				template<typename Service>
				void AddTransient()
				{
					auto creator = new TransientCreator<Service>();
					creator->Register();
					auto result = creatos_.insert(std::pair<TypeInfo, Creator*>(GET_TYPE_INFO(Service), creator));
					JUNJINJEN_ASSERT(result.second);
				}

				template<typename Service, typename Interface>
				void AddTransient(std::function<Service*()> creator)
				{
					static_assert(std::is_base_of<Interface, Service>::value, "Service should inherit Interface");
					auto creatorObj = new TransientCreator<Service>();
					creatorObj->Register(creator);
					auto result = creatos_.insert(std::pair<TypeInfo, Creator*>(GET_TYPE_INFO(Interface), creatorObj));
					JUNJINJEN_ASSERT(result.second);
				}

				template<typename Service, typename Interface>
				void AddTransient(std::function<std::shared_ptr<Service>()> creator)
				{
					static_assert(std::is_base_of<Interface, Service>::value, "Service should inherit Interface");
					auto creatorObj = new TransientCreator<Service>();
					creatorObj->Register(creator);
					auto result = creatos_.insert(std::pair<TypeInfo, Creator*>(GET_TYPE_INFO(Interface), creatorObj));
					JUNJINJEN_ASSERT(result.second);
				}

				template<typename Service>
				void AddTransient(std::function<Service*()> creator)
				{
					auto creatorObj = new TransientCreator<Service>();
					creatorObj->Register(creator);
					auto result = creatos_.insert(std::pair<TypeInfo, Creator*>(GET_TYPE_INFO(Service), creatorObj));
					JUNJINJEN_ASSERT(result.second);
				}

				template<typename Service>
				void AddTransient(std::function<std::shared_ptr<Service>()> creator)
				{
					auto creatorObj = new TransientCreator<Service>();
					creatorObj->Register(creator);
					auto result = creatos_.insert(std::pair<TypeInfo, Creator*>(GET_TYPE_INFO(Service), creatorObj));
					JUNJINJEN_ASSERT(result.second);
				}
			private:
				std::unordered_map<TypeInfo, Creator*> creatos_;
			};
		}
	}
}
