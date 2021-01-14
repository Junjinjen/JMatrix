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
					byte_string tmp;
					std::basic_ostringstream<uint8_t> stream(tmp);
					if (Serialize(stream))
					{
						return tmp;
					}

					return byte_string();
				}

				bool SerializableObject::Deserialize(const byte_string& string)
				{
					std::basic_istringstream<uint8_t> stream(string);
					return Deserialize(stream);
				}

				bool SerializableObject::Serialize(std::basic_ostream<uint8_t>& stream) const
				{
					return elementsConverter_.TrySetArray(stream, elements_);
				}

				bool SerializableObject::Deserialize(std::basic_istream<uint8_t>& stream)
				{
					return elementsConverter_.TryGetArray(stream, elements_);
				}

				std::vector<std::string> SerializableObject::GetNames() const
				{
					std::vector<std::string> answ;
					for (size_t i = 0; i < elements_.size(); i++)
					{
						answ.push_back(elements_[i].GetName());
					}

					return answ;
				}

				bool SerializableObject::HasValue(const std::string& name) const
				{
					for (size_t i = 0; i < elements_.size(); i++)
					{
						if (elements_[i].GetName() == name)
						{
							return true;
						}
					}

					return false;
				}

				Container SerializableObject::GetOrCreateContainerByName(const std::string& name)
				{
					for (size_t i = 0; i < elements_.size(); i++)
					{
						if (elements_[i].GetName() == name)
						{
							return elements_[i];
						}
					}

					Container tmp;
					tmp.SetName(name);
					return tmp;
				}

				Container* SerializableObject::GetContainerByName(const std::string& name)
				{
					for (size_t i = 0; i < elements_.size(); i++)
					{
						if (elements_[i].GetName() == name)
						{
							return &elements_[i];
						}
					}

					return nullptr;
				}
			}
		}
	}
}
