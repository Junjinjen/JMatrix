#pragma once
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
						namespace primitive_array_container
						{
							template<typename T>
							class PrimitiveArrayContainer : public ArrayContainer<T>
							{
							public:
								PrimitiveArrayContainer(container_type type);
								PrimitiveArrayContainer(container_type type, const T* elements, size_t elementsCount);
								PrimitiveArrayContainer(container_type type, const std::vector<T>& elements);
								PrimitiveArrayContainer(container_type type, std::vector<T>&& elements);

								virtual void Serialize(std::basic_ostream<uint8_t>& stream) const override;
								virtual bool Deserialize(std::basic_istream<uint8_t>& stream) override;
							};

							template<typename T>
							inline PrimitiveArrayContainer<T>::PrimitiveArrayContainer(container_type type)
								: ArrayContainer<T>(type)
							{
							}

							template<typename T>
							inline PrimitiveArrayContainer<T>::PrimitiveArrayContainer(container_type type, const T* elements, size_t elementsCount)
								: ArrayContainer<T>(type, elements, elementsCount)
							{
							}

							template<typename T>
							inline PrimitiveArrayContainer<T>::PrimitiveArrayContainer(container_type type, const std::vector<T>& elements)
								: ArrayContainer<T>(type, elements)
							{
							}

							template<typename T>
							inline PrimitiveArrayContainer<T>::PrimitiveArrayContainer(container_type type, std::vector<T>&& elements)
								: ArrayContainer<T>(type, elements)
							{
							}

							template<typename T>
							inline void PrimitiveArrayContainer<T>::Serialize(std::basic_ostream<uint8_t>& stream) const
							{
								if (!IsEmpty())
								{
									Container::Serialize(stream);

									size_t size = values_.size();
									stream.write((uint8_t*)&size, sizeof(size_t));
									for (size_t i = 0; i < size; i++)
									{
										auto value = values_[i];
										stream.write((uint8_t*)&value, sizeof(T));
									}
								}
							}

							template<typename T>
							inline bool PrimitiveArrayContainer<T>::Deserialize(std::basic_istream<uint8_t>& stream)
							{
								size_t size;
								stream.read((uint8_t*)&size, sizeof(size_t));

								values_.resize(size);
								for (size_t i = 0; i < size; i++)
								{
									T value;
									stream.read((uint8_t*)&value, sizeof(T));
									values_.push_back(value);
								}
								return stream.good();
							}
						}
					}
				}
			}
		}
	}
}
