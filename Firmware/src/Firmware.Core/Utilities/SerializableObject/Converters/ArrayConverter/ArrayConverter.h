#pragma once
#include "Utilities/SerializableObject/Converters/ValueConverter/ValueConverter.h"
#include <vector>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace utilities
		{
			namespace serializable_object
			{
				namespace converters
				{
					template<typename T>
					class ArrayConverter
					{
					public:
						bool TrySetArray(std::basic_ostream<uint8_t>& stream, const T* elements, int32_t elementsCount) const
						{
							ValueConverter<T> converter;
							stream.write((uint8_t*)&elementsCount, sizeof(int32_t));

							for (int32_t i = 0; i < elementsCount; i++)
							{
								if (!converter.TrySetValue(stream, elements[i]))
								{
									return false;
								}
							}

							return stream.good();
						}

						bool TrySetArray(std::basic_ostream<uint8_t>& stream, const std::vector<T>& elements) const
						{
							int32_t size = elements.size();
							ValueConverter<T> converter;
							stream.write((uint8_t*)&size, sizeof(int32_t));

							for (int32_t i = 0; i < size; i++)
							{
								if (!converter.TrySetValue(stream, elements[i]))
								{
									return false;
								}
							}

							return stream.good();
						}

						bool TryGetArray(std::basic_istream<uint8_t>& stream, std::vector<T>& elements) const
						{
							ValueConverter<T> converter;
							int32_t size;
							if (!stream.read((uint8_t*)&size, sizeof(int32_t)))
							{
								return false;
							}

							elements.resize(size);
							for (int32_t i = 0; i < size; i++)
							{
								if (!converter.TryGetValue(stream, elements[i]))
								{
									return false;
								}
							}

							return stream.good();
						}
					};
				}
			}
		}
	}
}
