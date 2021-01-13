#pragma once
#include <cstdint>

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
					enum class container_type : uint8_t
					{
						NotDefined	= 0b00000000,
						IsArray		= 0b10000000,
						Object		= 0b00000001,
						Buffer		= 0b00000010,
						Boolean		= 0b00000100,
						Int32		= 0b00001000,
						Int64		= 0b00010000,
					};

					inline container_type operator|(container_type a, container_type b)
					{
						return static_cast<container_type>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
					}

					inline container_type operator&(container_type a, container_type b)
					{
						return static_cast<container_type>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
					}

					inline container_type operator~(container_type a)
					{
						return static_cast<container_type>(~static_cast<uint8_t>(a));
					}

					inline container_type operator^(container_type a, container_type b)
					{
						return static_cast<container_type>(static_cast<uint8_t>(a) ^ static_cast<uint8_t>(b));
					}

					inline container_type& operator|=(container_type& a, container_type b)
					{
						return (container_type&)((uint8_t&)a |= (uint8_t)b);
					}

					inline container_type& operator&=(container_type& a, container_type b)
					{
						return (container_type&)((uint8_t&)a &= (uint8_t)b);
					}

					inline container_type& operator^=(container_type& a, container_type b)
					{
						return (container_type&)((uint8_t&)a ^= (uint8_t)b);
					}

					inline bool IsDefined(container_type type)
					{
						return type != container_type::NotDefined;
					}

					inline bool IsArray(container_type type)
					{
						return (uint8_t)(type & container_type::IsArray) != 0;
					}

					inline bool IsObject(container_type type)
					{
						return (uint8_t)(type & container_type::Object) != 0;
					}

					inline bool IsBuffer(container_type type)
					{
						return (uint8_t)(type & container_type::Buffer) != 0;
					}

					inline bool IsBoolean(container_type type)
					{
						return (uint8_t)(type & container_type::Boolean) != 0;
					}

					inline bool IsInt32(container_type type)
					{
						return (uint8_t)(type & container_type::Int32) != 0;
					}

					inline bool IsInt64(container_type type)
					{
						return (uint8_t)(type & container_type::Int64) != 0;
					}

					inline bool IsPrimitiveType(container_type type)
					{
						return IsBoolean(type) || IsInt32(type) || IsInt64(type);
					}
				}
			}
		}
	}
}
