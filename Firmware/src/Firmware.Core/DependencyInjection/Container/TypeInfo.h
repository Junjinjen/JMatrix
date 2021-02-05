#pragma once
#define GET_TYPE_INFO(type) __GetTypeInfo<type>()

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace dependency_injection
		{
			typedef void* TypeInfo;

			template<typename T>
			TypeInfo __GetTypeInfo()
			{
				static T* TypeUniqueMarker = nullptr;
				return &TypeUniqueMarker;
			}
		}
	}
}
