#pragma once
#include "Utilities/SerializableObject/SerializableInterface/Serializable.h"
#include <iostream>
#include <type_traits>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace utilities
		{
			namespace serializable_object
			{
				namespace converters
				{
					template<bool B, class T = void>
					using enable_if_t = typename std::enable_if<B, T>::type;

					template<typename T, typename U = void>
					class ValueConverter;
				}
			}
		}
	}
}
