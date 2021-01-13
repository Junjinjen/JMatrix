#include "SerializableObject.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace utilities
		{
			namespace serializable_object
			{
				byte_string SerializableObject::Serialize() const
				{
					std::basic_ostringstream<uint8_t> stream;
					Serialize(stream);

					return stream.str();
				}

				bool SerializableObject::Deserialize(const byte_string& string)
				{
					std::basic_istringstream<uint8_t> stream(string);
					return Deserialize(stream);
				}

				void SerializableObject::Serialize(std::basic_ostream<uint8_t>& stream) const
				{
					if (HasElements())
					{
						size_t size = elements_.size();
						stream.write((uint8_t*)&size, sizeof(size_t));

						for (auto& pair : elements_)
						{
							size_t nameSize = pair.first.size();
							stream.write((uint8_t*)&nameSize, sizeof(size_t));
							stream.write((uint8_t*)&pair.first[0], nameSize);

							pair.second->Serialize(stream);
						}
					}
				}

				bool SerializableObject::Deserialize(std::basic_istream<uint8_t>& stream)
				{
					size_t size;
					stream.read((uint8_t*)&size, sizeof(size_t));

					for (size_t i = 0; i < size; i++)
					{
						size_t nameSize;
						stream.read((uint8_t*)&nameSize, sizeof(size_t));

						std::string name;
						name.resize(nameSize);
						stream.read((uint8_t*)&name[0], nameSize);

						container::container_type type;
						stream.read((uint8_t*)&type, sizeof(container::container_type));

						Container* container = ContainerFactory::Create(type);
						if (!container->Deserialize(stream))
						{
							return false;
						}

						elements_.insert(std::make_pair(name, container));
					}
				}

				bool SerializableObject::HasElements() const
				{
					return !elements_.empty();
				}
			}
		}
	}
}
