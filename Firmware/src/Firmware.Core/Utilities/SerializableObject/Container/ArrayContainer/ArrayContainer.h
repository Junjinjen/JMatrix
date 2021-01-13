#pragma once
#include "Utilities/SerializableObject/Container/Container.h"
#include <vector>
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
					namespace array_container
					{
						template<typename T>
						class ArrayContainer : public Container
						{
						public:
							ArrayContainer(container_type type);
							ArrayContainer(container_type type, const T* elements, size_t elementsCount);
							ArrayContainer(container_type type, const std::vector<T>& values);
							ArrayContainer(container_type type, std::vector<T>&& values);

							bool IsEmpty() const;

							size_t GetSize() const;
							T& operator[](size_t index);

							void AddValue(T value);
							void EraseValue(size_t index);

							std::vector<T>& GetBuffer() const;
						protected:
							std::vector<T> values_;
						};

						template<typename T>
						inline ArrayContainer<T>::ArrayContainer(container_type type)
							: Container(type)
						{
							assert(IsArray());
						}

						template<typename T>
						inline ArrayContainer<T>::ArrayContainer(container_type type, const T* elements, size_t elementsCount)
							: Container(type), values_(elements, elements + elementsCount)
						{
							assert(IsArray());
						}

						template<typename T>
						inline ArrayContainer<T>::ArrayContainer(container_type type, const std::vector<T>& values)
							: Container(type), values_(values)
						{
							assert(IsArray());
						}

						template<typename T>
						inline ArrayContainer<T>::ArrayContainer(container_type type, std::vector<T>&& values)
							: Container(type), values_(values)
						{
							assert(IsArray());
						}

						template<typename T>
						inline bool ArrayContainer<T>::IsEmpty() const
						{
							return values_.empty();
						}

						template<typename T>
						inline size_t ArrayContainer<T>::GetSize() const
						{
							return values_.size();
						}

						template<typename T>
						inline T& ArrayContainer<T>::operator[](size_t index)
						{
							return values_[index];
						}

						template<typename T>
						inline void ArrayContainer<T>::AddValue(T value)
						{
							values_.push_back(value);
						}

						template<typename T>
						inline void ArrayContainer<T>::EraseValue(size_t index)
						{
							values_.erase(values_.begin() + index);
						}

						template<typename T>
						inline std::vector<T>& ArrayContainer<T>::GetBuffer() const
						{
							return values_;
						}
					}
				}
			}
		}
	}
}
