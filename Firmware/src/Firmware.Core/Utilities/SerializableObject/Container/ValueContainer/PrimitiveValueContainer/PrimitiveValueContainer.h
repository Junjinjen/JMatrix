#pragma once
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
						namespace primitive_value_container
						{
							template<typename T>
							class PrimitiveValueContainer : public ValueContainer<T>
							{
							public:
								PrimitiveValueContainer(container_type type);
								PrimitiveValueContainer(container_type type, const T value);

								virtual void Serialize(std::basic_ostream<uint8_t>& stream) const override;
								virtual bool Deserialize(std::basic_istream<uint8_t>& stream) override;
							};

							template<typename T>
							inline PrimitiveValueContainer<T>::PrimitiveValueContainer(container_type type)
								: ValueContainer<T>(type)
							{
							}

							template<typename T>
							inline PrimitiveValueContainer<T>::PrimitiveValueContainer(container_type type, const T value)
								: ValueContainer<T>(type, value)
							{
							}

							template<typename T>
							inline void PrimitiveValueContainer<T>::Serialize(std::basic_ostream<uint8_t>& stream) const
							{
								if (HasValue())
								{
									Container::Serialize(stream);
									stream.write((uint8_t*)&value_, sizeof(T));
								}
							}

							template<typename T>
							inline bool PrimitiveValueContainer<T>::Deserialize(std::basic_istream<uint8_t>& stream)
							{
								stream.read((uint8_t*)&value_, sizeof(T));
								return stream.good();
							}
						}
					}
				}
			}
		}
	}
}
