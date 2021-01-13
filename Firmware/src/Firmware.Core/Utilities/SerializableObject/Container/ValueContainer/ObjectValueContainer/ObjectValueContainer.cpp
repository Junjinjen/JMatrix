#include "ObjectValueContainer.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace utilities
		{
			namespace serializable_object
			{
				namespace container
				{
					namespace value_container
					{
						namespace object_value_container
						{
							ObjectContainer::ObjectContainer()
								: ValueContainer(container_type::Object)
							{
							}

							ObjectContainer::ObjectContainer(const SerializableObject& value)
								: ValueContainer(container_type::Object, value)
							{
							}

							ObjectContainer::ObjectContainer(SerializableObject&& value)
								: ValueContainer(container_type::Object, value)
							{
							}

							void ObjectContainer::Serialize(std::basic_ostream<uint8_t>& stream) const
							{
								if (HasValue())
								{
									Container::Serialize(stream);
									value_.Serialize(stream);
								}
							}

							bool ObjectContainer::Deserialize(std::basic_istream<uint8_t>& stream)
							{
								return value_.Deserialize(stream);
							}
						}
					}
				}
			}
		}
	}
}
