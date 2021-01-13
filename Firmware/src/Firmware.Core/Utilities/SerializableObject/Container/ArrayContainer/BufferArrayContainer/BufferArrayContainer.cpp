#include "BufferArrayContainer.h"

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
							BufferArrayContainer::BufferArrayContainer()
								: ArrayContainer<byte_string>(container_type::IsArray | container_type::Buffer)
							{
							}

							BufferArrayContainer::BufferArrayContainer(const byte_string* elements, size_t elementsCount)
								: ArrayContainer<byte_string>(container_type::IsArray | container_type::Buffer, elements, elementsCount)
							{
							}

							BufferArrayContainer::BufferArrayContainer(const std::vector<byte_string>& elements)
								: ArrayContainer<byte_string>(container_type::IsArray | container_type::Buffer, elements)
							{
							}

							BufferArrayContainer::BufferArrayContainer(std::vector<byte_string>&& elements)
								: ArrayContainer<byte_string>(container_type::IsArray | container_type::Buffer, elements)
							{
							}

							void BufferArrayContainer::Serialize(std::basic_ostream<uint8_t>& stream) const
							{
								if (!IsEmpty())
								{
									Container::Serialize(stream);

									size_t size = values_.size();
									stream.write((uint8_t*)&size, sizeof(size_t));

									for (size_t i = 0; i < size; i++)
									{
										size_t elementSize = values_[i].size();
										stream.write((uint8_t*)&elementSize, sizeof(size_t));
										stream.write((uint8_t*)&values_[i][0], elementSize);
									}
								}
							}

							bool BufferArrayContainer::Deserialize(std::basic_istream<uint8_t>& stream)
							{
								size_t size;
								stream.read((uint8_t*)&size, sizeof(size_t));

								for (size_t i = 0; i < size; i++)
								{
									byte_string tmp;
									size_t elementSize;

									if (!stream.read((uint8_t*)&elementSize, sizeof(size_t)))
									{
										return false;
									}

									tmp.resize(elementSize);
									stream.read(&tmp[0], elementSize);

									values_.push_back(std::move(tmp));
								}

								return stream.good();
							}
						}
					}
				}
			}
		}
	}
}
