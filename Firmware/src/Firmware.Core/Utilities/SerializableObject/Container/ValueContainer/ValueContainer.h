#pragma once
#include "Utilities/SerializableObject/Container/Container.h"
#include <cassert>

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
					namespace value_container
					{
						template<typename T>
						class ValueContainer : public Container
						{
						public:
							ValueContainer(container_type type);
							ValueContainer(container_type type, const T& value);
							ValueContainer(container_type type, T&& value);

							bool HasValue() const;
							const T& GetValue() const;
							T& GetValue();
							void SetValue(T value);
						protected:
							bool hasValue_;
							T value_;
						};

						template<typename T>
						inline ValueContainer<T>::ValueContainer(container_type type)
							: Container(type), hasValue_(false)
						{
							assert(!IsArray());
						}

						template<typename T>
						inline ValueContainer<T>::ValueContainer(container_type type, const T& value)
							: Container(type), value_(value), hasValue_(true)
						{
							assert(!IsArray());
						}

						template<typename T>
						inline ValueContainer<T>::ValueContainer(container_type type, T&& value)
							: Container(type), value_(value), hasValue_(true)
						{
							hasValue_ = true;
							assert(!IsArray());
						}

						template<typename T>
						inline bool ValueContainer<T>::HasValue() const
						{
							return hasValue_;
						}

						template<typename T>
						inline const T& ValueContainer<T>::GetValue() const
						{
							return value_;
						}

						template<typename T>
						inline T& ValueContainer<T>::GetValue()
						{
							return value_;
						}

						template<typename T>
						inline void ValueContainer<T>::SetValue(T value)
						{
							value_ = value;
						}
					}
				}
			}
		}
	}
}
