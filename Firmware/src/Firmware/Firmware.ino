#include "DependencyInjection/ContainerBuilder/ContainerBuilder.h"
#include "Services/TaskService/TaskService.h"
#include "Core/Core.h"

using junjinjen_matrix::firmware::logging::Logger;
using junjinjen_matrix::firmware::services::task_service::network_pipeline::network::NetworkServer;
using junjinjen_matrix::firmware::dependency_injection::ContainerBuilder;
using junjinjen_matrix::firmware::services::TaskService;

junjinjen_matrix::firmware::Core core;

void setup()
{
	// Register dependencies.
	ContainerBuilder builder;
	builder.AddSingleton<SomeLogger, Logger>();
	builder.AddSingleton<SomeNetworkServer, NetworkServer>();
	builder.AddSingleton<XmlSerializer, ContainerSerializer>();
	builder.Build();

	// Add services.
	core.RegisterService(new TaskService());

	core.Initialize();
}

void loop()
{
	core.Loop();
}
