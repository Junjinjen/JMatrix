#include "Container.h"

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
					const std::string& Container::GetName() const
					{
						return name_;
					}

					void Container::SetName(const std::string& name)
					{
						name_ = name;
					}

					void Container::SetName(std::string&& name)
					{
						name_ = std::move(name);
					}

					std::unique_ptr<std::basic_istream<uint8_t>> Container::GetReadStream() const
					{
						return std::unique_ptr<std::basic_istream<uint8_t>>(new std::basic_istringstream<uint8_t>(data_));
					}

					std::unique_ptr<std::basic_ostream<uint8_t>> Container::GetWriteStream() const
					{
						return std::unique_ptr<std::basic_ostream<uint8_t>>(new std::basic_ostringstream<uint8_t>(data_));
					}

					bool Container::Serialize(std::basic_ostream<uint8_t>& stream) const
					{
						size_t nameSize = name_.size();
						stream.write((uint8_t*)&nameSize, sizeof(size_t));
						stream.write((uint8_t*)&name_[0], nameSize);

						size_t dataSize = data_.size();
						stream.write((uint8_t*)&dataSize, sizeof(size_t));
						stream.write(&data_[0], dataSize);

						return stream.good();
					}

					bool Container::Deserialize(std::basic_istream<uint8_t>& stream)
					{
						size_t nameSize;
						if (!stream.read((uint8_t*)&nameSize, sizeof(size_t)))
						{
							return false;
						}

						name_.resize(nameSize);
						stream.read((uint8_t*)&name_[0], nameSize);

						size_t dataSize;
						if (!stream.read((uint8_t*)&dataSize, sizeof(size_t)))
						{
							return false;
						}

						data_.resize(dataSize);
						stream.read(&data_[0], dataSize);

						return stream.good();
					}
				}
			}
		}
	}
}
