#include "ObjectArrayContainer.h"

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
					namespace array_container
					{
						namespace object_array_container
						{
							ObjectArrayContainer::ObjectArrayContainer()
								: ArrayContainer(container_type::IsArray | container_type::Object)
							{
							}

							ObjectArrayContainer::ObjectArrayContainer(const SerializableObject* elements, size_t elementsCount)
								: ArrayContainer(container_type::IsArray | container_type::Object, elements, elementsCount)
							{
							}

							ObjectArrayContainer::ObjectArrayContainer(const std::vector<SerializableObject>& values)
								: ArrayContainer(container_type::IsArray | container_type::Object, values)
							{
							}

							ObjectArrayContainer::ObjectArrayContainer(std::vector<SerializableObject>&& values)
								: ArrayContainer(container_type::IsArray | container_type::Object, values)
							{
							}

							void ObjectArrayContainer::Serialize(std::basic_ostream<uint8_t>& stream) const
							{
								if (!IsEmpty())
								{
									Container::Serialize(stream);

									size_t size = values_.size();
									stream.write((uint8_t*)&size, sizeof(size_t));

									for (size_t i = 0; i < size; i++)
									{
										values_[i].Serialize(stream);
									}
								}
							}

							bool ObjectArrayContainer::Deserialize(std::basic_istream<uint8_t>& stream)
							{
								size_t size;
								stream.read((uint8_t*)&size, sizeof(size_t));

								for (size_t i = 0; i < size; i++)
								{
									SerializableObject tmp;
									if (!tmp.Deserialize(stream))
									{
										return false;
									}

									values_.push_back(std::move(tmp));
								}
							}
						}
					}
				}
			}
		}
	}
}
