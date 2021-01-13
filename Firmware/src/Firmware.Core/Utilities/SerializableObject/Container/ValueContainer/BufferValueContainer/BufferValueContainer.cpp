#include "BufferValueContainer.h"

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
							BufferContainer::BufferContainer()
								: ValueContainer<byte_string>(container_type::Buffer)
							{
							}

							BufferContainer::BufferContainer(const byte_string& value)
								: ValueContainer<byte_string>(container_type::Buffer, value)
							{
							}

							BufferContainer::BufferContainer(byte_string&& value)
								: ValueContainer<byte_string>(container_type::Buffer, value)
							{
							}

							void BufferContainer::Serialize(std::basic_ostream<uint8_t>& stream) const
							{
								if (HasValue())
								{
									size_t size = value_.size();
									stream.write((uint8_t*)&size, sizeof(size_t));
									stream.write(&value_[0], size);
								}
							}

							bool BufferContainer::Deserialize(std::basic_istream<uint8_t>& stream)
							{
								size_t size;
								stream.read((uint8_t*)&size, sizeof(size_t));

								value_.resize(size);
								stream.read(&value_[0], size);
								return stream.good();
							}
						}
					}
				}
			}
		}
	}
}
