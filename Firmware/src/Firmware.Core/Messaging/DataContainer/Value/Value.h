#pragma once
#include "Utilities/Assertion/AssertDefinition.h"
#include "Messaging/DataContainer/Container/DataContainerDefinition.h"
#include <cstdint>
#include <cstring>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace messaging
		{
			using utilities::byte_definitions::byte_string;

			enum ValueType
			{
				Empty,
				Int32,
				Int64,
				Boolean,
				String,
				ByteString,
				Float,
				Double,
				Container,
				Array
			};

			class Value
			{
			public:
				Value();
				Value(const Value& value);
				Value(Value&& value) noexcept;
				Value(bool value);
				Value(int32_t value);
				Value(int64_t value);
				Value(const std::string& value);
				Value(const char* value);
				Value(std::string&& value);
				Value(const byte_string& value);
				Value(byte_string&& value);
				Value(float value);
				Value(double value);
				Value(const DataContainer& value);
				Value(DataContainer&& value);
				Value(const std::vector<Value>& value);
				Value(std::vector<Value>&& value);
				~Value();

				void operator=(const Value& value);
				void operator=(Value&& value) noexcept;
				bool operator==(const Value& other) const;

				ValueType GetType() const;

				bool Empty() const;
				bool IsInt32() const;
				bool IsInt64() const;
				bool IsBoolean() const;
				bool IsString() const;
				bool IsByteString() const;
				bool IsFloat() const;
				bool IsDouble() const;
				bool IsArray() const;
				bool IsContainer() const;

				int32_t AsInt32() const;
				int64_t AsInt64() const;
				bool AsBoolean() const;
				const std::string& AsString() const;
				const byte_string& AsByteString() const;
				float AsFloat() const;
				double AsDouble() const;
				
				void Clear();
				void SetInt32(int32_t value);
				void SetInt64(int64_t value);
				void SetBoolean(bool value);
				void SetString(const std::string& value);
				void SetString(std::string&& value);
				void SetByteString(const byte_string& value);
				void SetByteString(byte_string&& value);
				void SetFloat(float value);
				void SetDouble(double value);
				
				DataContainer& AsContainer();
				const DataContainer& AsContainer() const;

				std::vector<Value>& AsArray();
				const std::vector<Value>& AsArray() const;

				DataContainer& CreateContainer();
				DataContainer& CreateContainer(const DataContainer& value);
				DataContainer& CreateContainer(DataContainer&& value);

				std::vector<Value>& CreateArray();
				std::vector<Value>& CreateArray(const std::vector<Value>& value);
				std::vector<Value>& CreateArray(std::vector<Value>&& value);
			private:
				ValueType type_;

				union ValueType_t
				{
#pragma warning(push)
#pragma warning(disable : 26495)
					ValueType_t() { }
#pragma warning(pop)
					~ValueType_t() { }

					int32_t int32_v;
					int64_t int64_v;
					bool bool_v;
					std::string string_v;
					byte_string byte_string_v;
					float float_v;
					double double_v;
					DataContainer container_v;
					std::vector<Value> array_v;
				} *value_;

				inline void RemoveValue();
				inline bool AllocateValue();
				inline void CopyUnion(const junjinjen_matrix::firmware::messaging::Value& other);
			};
		}
	}
}
