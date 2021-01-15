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
					using serializable_interface::Serializable;

					template<typename T>
					using only_if_serializable =
						enable_if_t<std::is_base_of<Serializable, T>::value>;

					template<typename T>
					class ValueConverter<T, only_if_serializable<T>>
					{
					public:
						bool TrySetValue(std::basic_ostream<uint8_t>& stream, const T& value)
						{
							return value.Serialize(stream);
						}

						bool TryGetValue(std::basic_istream<uint8_t>& stream, T& value)
						{
							return value.Deserialize(stream);
						}
					};
				}
			}
		}
	}
}
