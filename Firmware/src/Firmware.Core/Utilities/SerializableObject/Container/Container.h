#pragma once
#include "Utilities/ByteString/ByteString.h"
#include "Utilities/SerializableObject/SerializableInterface/Serializable.h"
#include <sstream>
#include <memory>

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
					using utilities::byte_string::byte_string;
					using serializable_interface::Serializable;

					class Container : public Serializable
					{
					public:
						const std::string& GetName() const;
						void SetName(const std::string& name);
						void SetName(std::string&& name);

						const byte_string& GetData() const;
						void SetData(const byte_string& str);
						void SetData(byte_string&& str);

						virtual bool Serialize(std::basic_ostream<uint8_t>& stream) const override;
						virtual bool Deserialize(std::basic_istream<uint8_t>& stream) override;
					private:
						std::string name_;
						byte_string data_;
					};
				}
			}
		}
	}
}
