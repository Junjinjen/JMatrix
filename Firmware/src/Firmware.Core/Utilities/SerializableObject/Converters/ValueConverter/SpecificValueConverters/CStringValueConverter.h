#pragma once
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
					using only_if_c_string =
						enable_if_t<std::is_same<T, const char*>::value || std::is_same<T, char*>::value>;

					template<typename T>
					class ValueConverter<T, only_if_c_string<T>>
					{
					public:
						bool TrySetValue(std::basic_ostream<uint8_t>& stream, const T value)
						{
							size_t size = strlen(value);
							stream.write((uint8_t*)&size, sizeof(size_t));
							stream.write((uint8_t*)&value[0], size);
							return stream.good();
						}
					};
				}
			}
		}
	}
}
