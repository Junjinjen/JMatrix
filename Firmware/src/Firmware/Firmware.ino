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
	ContainerBuilder builder;

	// Register dependencies.
	builder.AddSingleton<SomeLogger, Logger>();
	builder.AddSingleton<SomeNetworkServer, NetworkServer>();
	builder.AddSingleton<TaskService>();
	builder.Build();

	// Add services.
	core.AddService(RESOLVE_INSTANCE(TaskService));

	JUNJINJEN_ASSERT(core.Initialize());
}

void loop()
{
	core.Loop();
}
