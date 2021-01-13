#pragma once
#include "Utilities/ByteString/ByteString.h"
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
						namespace buffer_array_container
						{
							using utilities::byte_string::byte_string;

							class BufferArrayContainer : public ArrayContainer<byte_string>
							{
							public:
								BufferArrayContainer();
								BufferArrayContainer(const byte_string* elements, size_t elementsCount);
								BufferArrayContainer(const std::vector<byte_string>& elements);
								BufferArrayContainer(std::vector<byte_string>&& elements);

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
