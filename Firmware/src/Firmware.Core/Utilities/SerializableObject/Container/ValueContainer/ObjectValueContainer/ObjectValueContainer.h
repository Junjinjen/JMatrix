#pragma once
#include "Utilities/SerializableObject/SerializableObject.h"
#include "Utilities/SerializableObject/Container/ValueContainer/ValueContainer.h"

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
							class ObjectContainer : public ValueContainer<SerializableObject>
							{
							public:
								ObjectContainer();
								ObjectContainer(const SerializableObject& value);
								ObjectContainer(SerializableObject&&value);

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
