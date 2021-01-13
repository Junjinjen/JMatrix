#pragma once
#include "Utilities/SerializableObject/SerializableObject.h"
#include "Utilities/SerializableObject/Container/ArrayContainer/ArrayContainer.h"

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
							class ObjectArrayContainer : public ArrayContainer<SerializableObject>
							{
							public:
								ObjectArrayContainer();
								ObjectArrayContainer(const SerializableObject* elements, size_t elementsCount);
								ObjectArrayContainer(const std::vector<SerializableObject>& values);
								ObjectArrayContainer(std::vector<SerializableObject>&& values);

								virtual void Serialize(std::basic_ostream<uint8_t>& stream) const override;
								virtual bool Deserialize(std::basic_istream<uint8_t>& stream) override;
							};
						}
					}
				}
			}
		}
	}
}
