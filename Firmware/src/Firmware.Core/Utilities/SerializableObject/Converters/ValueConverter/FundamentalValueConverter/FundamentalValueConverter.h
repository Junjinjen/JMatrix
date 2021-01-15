#pragma once
#include "Utilities/SerializableObject/Converters/ValueConverter/ValueConverterClassDefenition.h"

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
					using only_if_fundamental =
						enable_if_t<std::is_fundamental<T>::value>;

					template<typename T>
					class ValueConverter<T, only_if_fundamental<T>>
					{
					public:
						bool TrySetValue(std::basic_ostream<uint8_t>& stream, const T value)
						{
							stream.write((uint8_t*)&value, sizeof(T));
							return stream.good();
						}

						bool TryGetValue(std::basic_istream<uint8_t>& stream, T& value)
						{
							stream.read((uint8_t*)&value, sizeof(T));
							return stream.good();
						}
					};
				}
			}
		}
	}
}
