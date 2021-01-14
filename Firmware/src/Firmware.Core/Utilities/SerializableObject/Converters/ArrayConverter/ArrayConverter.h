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
						void SetValue(std::basic_ostream<uint8_t>& stream, const T* elements, size_t elementsCount);
						void SetValue(std::basic_ostream<uint8_t>& stream, const std::vector<T>& elements);

						bool TryGetValue(std::basic_istream<uint8_t>& stream, std::vector<T>& elements);
					};
				}
			}
		}
	}
}
