#pragma once
#include "Utilities/ByteString/ByteString.h"
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
						namespace buffer_value_container
						{
							using utilities::byte_string::byte_string;

							class BufferContainer : public ValueContainer<byte_string>
							{
							public:
								BufferContainer();
								BufferContainer(const byte_string& value);
								BufferContainer(byte_string&& value);

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
