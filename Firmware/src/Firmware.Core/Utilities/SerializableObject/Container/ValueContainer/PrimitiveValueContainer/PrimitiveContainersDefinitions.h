#pragma once
#include "Utilities/SerializableObject/Container/ValueContainer/PrimitiveValueContainer/PrimitiveValueContainer.h"

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
						namespace primitive_value_container
						{
							class BooleanContainer : public PrimitiveValueContainer<bool>
							{
							public:
								BooleanContainer()
									: PrimitiveValueContainer(container_type::Boolean)
								{
								}

								BooleanContainer(const bool value)
									: PrimitiveValueContainer(container_type::Boolean, value)
								{
								}
							};

							class Int32Container : public PrimitiveValueContainer<int32_t>
							{
							public:
								Int32Container()
									: PrimitiveValueContainer(container_type::Int32)
								{
								}

								Int32Container(const int32_t value)
									: PrimitiveValueContainer(container_type::Int32, value)
								{
								}
							};

							class Int64Container : public PrimitiveValueContainer<int64_t>
							{
							public:
								Int64Container()
									: PrimitiveValueContainer(container_type::Int64)
								{
								}

								Int64Container(const int64_t value)
									: PrimitiveValueContainer(container_type::Int64, value)
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
