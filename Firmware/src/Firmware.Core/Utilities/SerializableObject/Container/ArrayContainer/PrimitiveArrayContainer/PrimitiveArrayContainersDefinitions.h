#pragma once
#include "Utilities/SerializableObject/Container/ArrayContainer/PrimitiveArrayContainer/PrimitiveArrayContainer.h"

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
						namespace primitive_array_container
						{
							class BooleanArrayContainer : public PrimitiveArrayContainer<bool>
							{
							public:
								BooleanArrayContainer()
									: PrimitiveArrayContainer(container_type::IsArray | container_type::Boolean)
								{
								}

								BooleanArrayContainer(const bool* elements, size_t elementsCount)
									: PrimitiveArrayContainer(container_type::IsArray | container_type::Boolean, elements, elementsCount)
								{
								}

								BooleanArrayContainer(const std::vector<bool>& elements)
									: PrimitiveArrayContainer(container_type::IsArray | container_type::Boolean, elements)
								{
								}

								BooleanArrayContainer(const std::vector<bool>&& elements)
									: PrimitiveArrayContainer(container_type::IsArray | container_type::Boolean, elements)
								{
								}
							};

							class Int32ArrayContainer : public PrimitiveArrayContainer<int32_t>
							{
							public:
								Int32ArrayContainer()
									: PrimitiveArrayContainer(container_type::IsArray | container_type::Int32)
								{
								}

								Int32ArrayContainer(const int32_t* elements, size_t elementsCount)
									: PrimitiveArrayContainer(container_type::IsArray | container_type::Int32, elements, elementsCount)
								{
								}

								Int32ArrayContainer(const std::vector<int32_t>& elements)
									: PrimitiveArrayContainer(container_type::IsArray | container_type::Int32, elements)
								{
								}

								Int32ArrayContainer(std::vector<int32_t>&& elements)
									: PrimitiveArrayContainer(container_type::IsArray | container_type::Int32, elements)
								{
								}
							};

							class Int64ArrayContainer : public PrimitiveArrayContainer<int64_t>
							{
							public:
								Int64ArrayContainer()
									: PrimitiveArrayContainer(container_type::IsArray | container_type::Int64)
								{
								}

								Int64ArrayContainer(const int64_t* elements, size_t elementsCount)
									: PrimitiveArrayContainer(container_type::IsArray | container_type::Int64, elements, elementsCount)
								{
								}

								Int64ArrayContainer(const std::vector<int64_t>& elements)
									: PrimitiveArrayContainer(container_type::IsArray | container_type::Int64, elements)
								{
								}

								Int64ArrayContainer(std::vector<int64_t>&& elements)
									: PrimitiveArrayContainer(container_type::IsArray | container_type::Int64, elements)
								{
								}
							};
						}
					}
				}
			}
		}
	}
}
