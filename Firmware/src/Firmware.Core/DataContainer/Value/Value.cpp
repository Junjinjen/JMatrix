#include "Value.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace data_container
		{
			Value::Value()
				: type_(ValueType::Empty)
			{
			}

			Value::Value(const Value& value)
				: type_(value.type_)
			{
				std::memcpy(&value_, &value.value_, sizeof(Value));
			}

			Value::Value(Value&& value)
				: type_(value.type_)
			{
				std::memcpy(&value_, &value.value_, sizeof(Value));
			}

			Value::Value(int32_t value)
			{
				value_.int32_v = value;
				type_ = ValueType::Int32;
			}

			Value::Value(int64_t value)
			{
				value_.int64_v = value;
				type_ = ValueType::Int64;
			}

			Value::Value(bool value)
			{
				value_.bool_v = value;
				type_ = ValueType::Boolean;
			}

			Value::Value(const std::string& value)
			{
				new (&value_.string_v) std::string(value);
				type_ = ValueType::String;
			}

			Value::Value(const char* value)
				: Value(std::string(value))
			{
			}

			Value::Value(std::string&& value)
			{
				new (&value_.string_v) std::string(value);
				type_ = ValueType::String;
			}

			Value::Value(const byte_string& value)
			{
				new (&value_.byte_string_v) byte_string(value);
				type_ = ValueType::ByteString;
			}

			Value::Value(byte_string&& value)
			{
				new (&value_.byte_string_v) byte_string(value);
				type_ = ValueType::ByteString;
			}

			Value::Value(float value)
			{
				value_.float_v = value;
				type_ = ValueType::Float;
			}

			Value::Value(double value)
			{
				value_.double_v = value;
				type_ = ValueType::Double;
			}

			Value::Value(const DataContainer& value)
			{
				new (&value_.container_v) DataContainer(value);
				type_ = ValueType::Container;
			}

			Value::Value(const std::vector<Value>& value)
			{
				new (&value_.array_v) std::vector<Value>(value);
				type_ = ValueType::Array;
			}

			Value::~Value()
			{
				RemoveValue();
			}

			void Value::operator=(const Value& value)
			{
				type_ = value.type_;
				std::memcpy(&value_, &value.value_, sizeof(Value));
			}

			ValueType Value::GetType() const
			{
				return type_;
			}

			bool Value::Empty() const
			{
				return type_ == ValueType::Empty;
			}

			bool Value::IsInt32() const
			{
				return type_ == ValueType::Int32;
			}

			bool Value::IsInt64() const
			{
				return type_ == ValueType::Int64;
			}

			bool Value::IsBoolean() const
			{
				return type_ == ValueType::Boolean;
			}

			bool Value::IsString() const
			{
				return type_ == ValueType::String;
			}

			bool Value::IsByteString() const
			{
				return type_ == ValueType::ByteString;
			}

			bool Value::IsFloat() const
			{
				return type_ == ValueType::Float;
			}

			bool Value::IsDouble() const
			{
				return type_ == ValueType::Double;
			}

			bool Value::IsArray() const
			{
				return type_ == ValueType::Array;
			}

			bool Value::IsContainer() const
			{
				return type_ == ValueType::Container;
			}

			int32_t Value::GetInt32() const
			{
				if (!IsInt32())
				{
					throw InvalidTypeException();
				}

				return value_.int32_v;
			}

			int64_t Value::GetInt64() const
			{
				if (!IsInt64())
				{
					throw InvalidTypeException();
				}

				return value_.int64_v;
			}

			bool Value::GetBoolean() const
			{
				if (!IsBoolean())
				{
					throw InvalidTypeException();
				}

				return value_.bool_v;
			}

			const std::string& Value::GetString() const
			{
				if (!IsString())
				{
					throw InvalidTypeException();
				}

				return value_.string_v;
			}

			const byte_string& Value::GetByteString() const
			{
				if (!IsByteString())
				{
					throw InvalidTypeException();
				}

				return value_.byte_string_v;
			}

			float Value::GetFloat() const
			{
				if (!IsFloat())
				{
					throw InvalidTypeException();
				}

				return value_.float_v;
			}

			double Value::GetDouble() const
			{
				if (!IsDouble())
				{
					throw InvalidTypeException();
				}

				return value_.double_v;
			}

			DataContainer& Value::AsContainer()
			{
				if (!IsContainer())
				{
					throw InvalidTypeException();
				}

				return value_.container_v;
			}

			std::vector<Value>& Value::AsArray()
			{
				if (!IsArray())
				{
					throw InvalidTypeException();
				}

				return value_.array_v;
			}

			void Value::Clear()
			{
				RemoveValue();
				type_ = ValueType::Empty;
			}

			void Value::SetInt32(int32_t value)
			{
				RemoveValue();
				value_.int32_v = value;
				type_ = ValueType::Int32;
			}

			void Value::SetInt64(int64_t value)
			{
				RemoveValue();
				value_.int64_v = value;
				type_ = ValueType::Int64;
			}

			void Value::SetBoolean(bool value)
			{
				RemoveValue();
				value_.bool_v = value;
				type_ = ValueType::Boolean;
			}

			void Value::SetString(const std::string& value)
			{
				RemoveValue();
				new (&value_.string_v) std::string(value);
				type_ = ValueType::String;
			}

			void Value::SetString(std::string&& value)
			{
				RemoveValue();
				new (&value_.string_v) std::string(value);
				type_ = ValueType::String;
			}

			void Value::SetByteString(const byte_string& value)
			{
				RemoveValue();
				new (&value_.byte_string_v) byte_string(value);
				type_ = ValueType::ByteString;
			}

			void Value::SetByteString(byte_string&& value)
			{
				RemoveValue();
				new (&value_.byte_string_v) byte_string(value);
				type_ = ValueType::ByteString;
			}

			void Value::SetFloat(float value)
			{
				RemoveValue();
				value_.float_v = value;
				type_ = ValueType::Float;
			}

			void Value::SetDouble(double value)
			{
				RemoveValue();
				value_.double_v = value;
				type_ = ValueType::Double;
			}

			DataContainer& Value::CreateContainer()
			{
				RemoveValue();
				new (&value_.container_v) DataContainer();
				type_ = ValueType::Container;
				return value_.container_v;
			}

			DataContainer& Value::CreateContainer(const DataContainer& value)
			{
				RemoveValue();
				new (&value_.container_v) DataContainer(value);
				type_ = ValueType::Container;
				return value_.container_v;
			}

			DataContainer& Value::CreateContainer(DataContainer&& value)
			{
				RemoveValue();
				new (&value_.container_v) DataContainer(value);
				type_ = ValueType::Container;
				return value_.container_v;
			}

			std::vector<Value>& Value::CreateArray()
			{
				RemoveValue();
				new (&value_.array_v) std::vector<Value>();
				type_ = ValueType::Array;
				return value_.array_v;
			}

			std::vector<Value>& Value::CreateArray(const std::vector<Value>& value)
			{
				RemoveValue();
				new (&value_.array_v) std::vector<Value>(value);
				type_ = ValueType::Array;
				return value_.array_v;
			}

			std::vector<Value>& Value::CreateArray(std::vector<Value>&& value)
			{
				RemoveValue();
				new (&value_.array_v) std::vector<Value>(value);
				type_ = ValueType::Array;
				return value_.array_v;
			}

			inline void Value::RemoveValue()
			{
				if (IsString() || IsByteString())
				{
					value_.string_v.~basic_string();
				}
				else if (IsArray())
				{
					value_.array_v.~vector();
				}
				else if (IsContainer())
				{
					value_.container_v.~DataContainer();
				}
			}
		}
	}
}
