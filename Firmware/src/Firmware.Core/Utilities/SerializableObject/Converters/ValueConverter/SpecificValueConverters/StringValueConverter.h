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
					using only_if_string =
						enable_if_t<std::is_same<std::string, T>::value>;

					template<typename T>
					class ValueConverter<T, only_if_string<T>>
					{
					public:
						bool TrySetValue(std::basic_ostream<uint8_t>& stream, const T& value)
						{
							int32_t size = value.size();
							stream.write((uint8_t*)&size, sizeof(int32_t));
							stream.write((uint8_t*)&value[0], size);
							return stream.good();
						}

						bool TryGetValue(std::basic_istream<uint8_t>& stream, T& value)
						{
							int32_t size;
							if (!stream.read((uint8_t*)&size, sizeof(int32_t)))
							{
								return false;
							}

							value.resize(size);
							stream.read((uint8_t*)&value[0], size);
							return stream.good();
						}
					};
				}
			}
		}
	}
}
