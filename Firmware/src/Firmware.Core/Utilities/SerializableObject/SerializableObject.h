#pragma once
#include "Utilities/SerializableObject/SerializableInterface/Serializable.h"
#include "Utilities/SerializableObject/Container/ValueContainer/PrimitiveValueContainer/PrimitiveContainersDefinitions.h"
#include "Utilities/SerializableObject/Container/ValueContainer/BufferValueContainer/BufferValueContainer.h"
#include "Utilities/SerializableObject/Container/ArrayContainer/PrimitiveArrayContainer/PrimitiveArrayContainersDefinitions.h"
#include "Utilities/SerializableObject/Container/ArrayContainer/BufferArrayContainer/BufferArrayContainer.h"
#include "Utilities/SerializableObject/ContainerFactory/ContainerFactory.h"
#include "Utilities/ByteString/ByteString.h"
#include <iostream>
#include <sstream>
#include <map>

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
						namespace object_value_container
						{
							class ObjectContainer;
						}
					}

					namespace array_container
					{
						namespace object_array_container
						{
							class ObjectArrayContainer;
						}
					}
				}

				using serializable_interface::Serializable;
				using container::Container;
				using utilities::byte_string::byte_string;
				using container::array_container::ArrayContainer;
				using container::value_container::ValueContainer;

				using container::array_container::buffer_array_container::BufferArrayContainer;
				using container::array_container::object_array_container::ObjectArrayContainer;
				using container::array_container::primitive_array_container::BooleanArrayContainer;
				using container::array_container::primitive_array_container::Int32ArrayContainer;
				using container::array_container::primitive_array_container::Int64ArrayContainer;

				using container::value_container::buffer_value_container::BufferContainer;
				using container::value_container::object_value_container::ObjectContainer;
				using container::value_container::primitive_value_container::BooleanContainer;
				using container::value_container::primitive_value_container::Int32Container;
				using container::value_container::primitive_value_container::Int64Container;

				using utilities::serializable_object::container_factory::ContainerFactory;

				class SerializableObject : public Serializable
				{
				public:
					byte_string Serialize() const;
					bool Deserialize(const byte_string& string);

					virtual void Serialize(std::basic_ostream<uint8_t>& stream) const override;
					virtual bool Deserialize(std::basic_istream<uint8_t>& stream) override;

					bool HasElements() const;

					Int32Container* CreateInt32Container(const std::string& name);
					Int64Container* CreateInt64Container(const std::string& name);
					BooleanContainer* CreateBooleanContainer(const std::string& name);
					ObjectContainer* CreateObjectContainer(const std::string& name);
					BufferContainer* CreateBufferContainer(const std::string& name);

					Int32ArrayContainer* CreateInt32ArrayContainer(const std::string& name);
					Int64ArrayContainer* CreateInt64ArrayContainer(const std::string& name);
					BooleanArrayContainer* CreateBooleanArrayContainer(const std::string& name);
					ObjectArrayContainer* CreateObjectArrayContainer(const std::string& name);
					BufferArrayContainer* CreateBufferArrayContainer(const std::string& name);
				private:
					std::map<std::string, Container*> elements_;
				};
			}
		}
	}
}
