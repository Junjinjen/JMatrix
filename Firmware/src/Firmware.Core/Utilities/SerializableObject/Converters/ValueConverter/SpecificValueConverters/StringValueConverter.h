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
					template<>
					class ValueConverter<std::string, void>
					{
					public:
						bool TrySetValue(std::basic_ostream<uint8_t>& stream, const std::string& value)
						{
							size_t size = value.size();
							stream.write((uint8_t*)&size, sizeof(size_t));
							stream.write((uint8_t*)&value[0], size);
							return stream.good();
						}

						bool TryGetValue(std::basic_istream<uint8_t>& stream, std::string& value)
						{
							size_t size;
							if (!stream.read((uint8_t*)&size, sizeof(size_t)))
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
