#pragma once
#include "Utilities/SerializableObject/Container/ContainerType.h"
#include "Utilities/SerializableObject/SerializableInterface/Serializable.h"

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
					using serializable_interface::Serializable;

					class Container : public Serializable
					{
					public:
						Container(container_type type);

						bool IsDefined() const;
						bool IsArray() const;
						bool IsObject() const;
						bool IsBuffer() const;
						bool IsBoolean() const;
						bool IsInt32() const;
						bool IsInt64() const;
						bool IsPrimitiveType() const;

						virtual void Serialize(std::basic_ostream<uint8_t>& stream) const override;
					protected:
						container_type type_;
					};
				}
			}
		}
	}
}
