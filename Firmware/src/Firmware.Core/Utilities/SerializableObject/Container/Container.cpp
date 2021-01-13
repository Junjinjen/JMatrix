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
					Container::Container(container_type type)
						: type_(type)
					{
					}

					bool Container::IsDefined() const
					{
						return container::IsDefined(type_);
					}

					bool Container::IsArray() const
					{
						return container::IsArray(type_);
					}

					bool Container::IsObject() const
					{
						return container::IsObject(type_);
					}

					bool Container::IsBuffer() const
					{
						return container::IsBuffer(type_);
					}

					bool Container::IsBoolean() const
					{
						return container::IsBoolean(type_);
					}

					bool Container::IsInt32() const
					{
						return container::IsInt32(type_);
					}

					bool Container::IsInt64() const
					{
						return container::IsInt64(type_);
					}

					bool Container::IsPrimitiveType() const
					{
						return container::IsPrimitiveType(type_);
					}

					void Container::Serialize(std::basic_ostream<uint8_t>& stream) const
					{
						stream.write((uint8_t*)&type_, sizeof(container_type));
					}
				}
			}
		}
	}
}
