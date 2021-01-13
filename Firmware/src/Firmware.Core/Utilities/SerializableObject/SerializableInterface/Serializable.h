#pragma once
#include <iostream>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace utilities
		{
			namespace serializable_object
			{
				namespace serializable_interface
				{
					class Serializable
					{
					public:
						void Serialize(std::basic_ostream<uint8_t>& stream) const;
						bool Deserialize(std::basic_istream<uint8_t>& stream);
					};
				}
			}
		}
	}
}
