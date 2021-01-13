#include "ContainerFactory.h"

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
					Container* ContainerFactory::Create(container_type type)
					{
						if (!container::IsDefined(type))
						{
							return nullptr;
						}

						if (container::IsArray(type))
						{
							if (container::IsBoolean(type))
							{
								return new container::array_container::primitive_array_container::BooleanArrayContainer();
							}
							else if (container::IsInt32(type))
							{
								return new container::array_container::primitive_array_container::Int32ArrayContainer();
							}
							else if (container::IsInt64(type))
							{
								return new container::array_container::primitive_array_container::Int64ArrayContainer();
							}
							else if (container::IsBuffer(type))
							{
								return new container::array_container::buffer_array_container::BufferArrayContainer();
							}
							else if (container::IsObject(type))
							{
								return new container::array_container::object_array_container::ObjectArrayContainer();
							}
						}
						else
						{
							if (container::IsBoolean(type))
							{
								return new container::value_container::primitive_value_container::BooleanContainer();
							}
							else if (container::IsInt32(type))
							{
								return new container::value_container::primitive_value_container::Int32Container();
							}
							else if (container::IsInt64(type))
							{
								return new container::value_container::primitive_value_container::Int64Container();
							}
							else if (container::IsBuffer(type))
							{
								return new container::value_container::buffer_value_container::BufferContainer();
							}
							else if (container::IsObject(type))
							{
								return new container::value_container::object_value_container::ObjectContainer();
							}
						}
					}
				}
			}
		}
	}
}
