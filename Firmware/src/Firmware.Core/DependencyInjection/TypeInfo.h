#pragma once
#include <stdio.h>

#if defined(__clang__)
#if __has_feature(cxx_rtti)
#define RTTI_ENABLED
#endif
#elif defined(__GNUG__)
#if defined(__GXX_RTTI)
#define RTTI_ENABLED
#endif
#elif defined(_MSC_VER)
#if defined(_CPPRTTI)
#define RTTI_ENABLED
#endif
#endif

#if defined(RTTI_ENABLED)
#include <typeindex>
typedef std::type_index TypeInfo;
#define GET_TYPE_INFO(type) typeid(type)
#else
typedef void* TypeInfo;

template<typename T>
TypeInfo __GetTypeInfo()
{
	static T* TypeUniqueMarker = nullptr;
	return &TypeUniqueMarker;
}

#define GET_TYPE_INFO(type) __GetTypeInfo<type>()
#endif