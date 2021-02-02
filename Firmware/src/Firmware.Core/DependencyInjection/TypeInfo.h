#pragma once
typedef void* TypeInfo;

template<typename T>
TypeInfo __GetTypeInfo()
{
	static T* TypeUniqueMarker = nullptr;
	return &TypeUniqueMarker;
}

#define GET_TYPE_INFO(type) __GetTypeInfo<type>()