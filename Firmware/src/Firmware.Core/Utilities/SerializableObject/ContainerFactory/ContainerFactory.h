#pragma once
#include "Utilities/SerializableObject/Container/Container.h"
#include "Utilities/SerializableObject/Container/ArrayContainer/BufferArrayContainer/BufferArrayContainer.h"
#include "Utilities/SerializableObject/Container/ArrayContainer/PrimitiveArrayContainer/PrimitiveArrayContainersDefinitions.h"
#include "Utilities/SerializableObject/Container/ArrayContainer/ObjectArrayContainer/ObjectArrayContainer.h"
#include "Utilities/SerializableObject/Container/ValueContainer/BufferValueContainer/BufferValueContainer.h"
#include "Utilities/SerializableObject/Container/ValueContainer/PrimitiveValueContainer/PrimitiveContainersDefinitions.h"
#include "Utilities/SerializableObject/Container/ValueContainer/ObjectValueContainer/ObjectValueContainer.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace utilities
		{
			namespace serializable_object
			{
				namespace container_factory
				{
					using container::Container;
					using container::container_type;

					class ContainerFactory
					{
					public:
						static Container* Create(container_type type);
					};
				}
			}
		}
	}
}
