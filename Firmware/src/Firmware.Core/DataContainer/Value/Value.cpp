#include "Value.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace data_container
		{
			Value::Value()
				: type_(ValueType::Empty), value_(nullptr)
			{
			}

			Value::Value(const Value& value)
				: type_(value.type_)
			{
				value_ = new ValueType_t();
				CopyUnion(value);
			}

			Value::Value(Value&& value)
				: type_(value.type_), value_(value.value_)
			{
				value.value_ = nullptr;
				value.type_ = ValueType::Empty;
			}

			Value::Value(int32_t value)
			{
				value_ = new ValueType_t();
				value_->int32_v = value;
				type_ = ValueType::Int32;
			}

			Value::Value(int64_t value)
			{
				value_ = new ValueType_t();
				value_->int64_v = value;
				type_ = ValueType::Int64;
			}

			Value::Value(bool value)
			{
				value_ = new ValueType_t();
				value_->bool_v = value;
				type_ = ValueType::Boolean;
			}

			Value::Value(const std::string& value)
			{
				value_ = new ValueType_t();
				new (&value_->string_v) std::string(value);
				type_ = ValueType::String;
			}

			Value::Value(const char* value)
				: Value(std::string(value))
			{
			}

			Value::Value(std::string&& value)
			{
				value_ = new ValueType_t();
				new (&value_->string_v) std::string(value);
				type_ = ValueType::String;
			}

			Value::Value(const byte_string& value)
			{
				value_ = new ValueType_t();
				new (&value_->byte_string_v) byte_string(value);
				type_ = ValueType::ByteString;
			}

			Value::Value(byte_string&& value)
			{
				value_ = new ValueType_t();
				new (&value_->byte_string_v) byte_string(value);
				type_ = ValueType::ByteString;
			}

			Value::Value(float value)
			{
				value_ = new ValueType_t();
				value_->float_v = value;
				type_ = ValueType::Float;
			}

			Value::Value(double value)
			{
				value_ = new ValueType_t();
				value_->double_v = value;
				type_ = ValueType::Double;
			}

			Value::Value(const DataContainer& value)
			{
				value_ = new ValueType_t();
				new (&value_->container_v) DataContainer(value);
				type_ = ValueType::Container;
			}

			Value::Value(const std::vector<Value>& value)
			{
				value_ = new ValueType_t();
				new (&value_->array_v) std::vector<Value>(value);
				type_ = ValueType::Array;
			}

			Value::~Value()
			{
				if (value_ != nullptr)
				{
					RemoveValue();
					delete value_;
				}
			}

			void Value::operator=(const Value& value)
			{
				if (!AllocateValue())
				{
					RemoveValue();
				}

				type_ = value.type_;
				CopyUnion(value);
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

				return value_->int32_v;
			}

			int64_t Value::GetInt64() const
			{
				if (!IsInt64())
				{
					throw InvalidTypeException();
				}

				return value_->int64_v;
			}

			bool Value::GetBoolean() const
			{
				if (!IsBoolean())
				{
					throw InvalidTypeException();
				}

				return value_->bool_v;
			}

			const std::string& Value::GetString() const
			{
				if (!IsString())
				{
					throw InvalidTypeException();
				}

				return value_->string_v;
			}

			const byte_string& Value::GetByteString() const
			{
				if (!IsByteString())
				{
					throw InvalidTypeException();
				}

				return value_->byte_string_v;
			}

			float Value::GetFloat() const
			{
				if (!IsFloat())
				{
					throw InvalidTypeException();
				}

				return value_->float_v;
			}

			double Value::GetDouble() const
			{
				if (!IsDouble())
				{
					throw InvalidTypeException();
				}

				return value_->double_v;
			}

			DataContainer& Value::AsContainer()
			{
				if (!IsContainer())
				{
					throw InvalidTypeException();
				}

				return value_->container_v;
			}

			std::vector<Value>& Value::AsArray()
			{
				if (!IsArray())
				{
					throw InvalidTypeException();
				}

				return value_->array_v;
			}

			void Value::Clear()
			{
				if (value_ != nullptr)
				{
					RemoveValue();

					delete value_;
					value_ = nullptr;
				}
				
				type_ = ValueType::Empty;
			}

			void Value::SetInt32(int32_t value)
			{
				if (!AllocateValue())
				{
					RemoveValue();
				}

				value_->int32_v = value;
				type_ = ValueType::Int32;
			}

			void Value::SetInt64(int64_t value)
			{
				if (!AllocateValue())
				{
					RemoveValue();
				}

				value_->int64_v = value;
				type_ = ValueType::Int64;
			}

			void Value::SetBoolean(bool value)
			{
				if (!AllocateValue())
				{
					RemoveValue();
				}

				value_->bool_v = value;
				type_ = ValueType::Boolean;
			}

			void Value::SetString(const std::string& value)
			{
				if (!AllocateValue())
				{
					RemoveValue();
				}

				new (&value_->string_v) std::string(value);
				type_ = ValueType::String;
			}

			void Value::SetString(std::string&& value)
			{
				if (!AllocateValue())
				{
					RemoveValue();
				}

				new (&value_->string_v) std::string(value);
				type_ = ValueType::String;
			}

			void Value::SetByteString(const byte_string& value)
			{
				if (!AllocateValue())
				{
					RemoveValue();
				}

				new (&value_->byte_string_v) byte_string(value);
				type_ = ValueType::ByteString;
			}

			void Value::SetByteString(byte_string&& value)
			{
				if (!AllocateValue())
				{
					RemoveValue();
				}

				new (&value_->byte_string_v) byte_string(value);
				type_ = ValueType::ByteString;
			}

			void Value::SetFloat(float value)
			{
				if (!AllocateValue())
				{
					RemoveValue();
				}

				value_->float_v = value;
				type_ = ValueType::Float;
			}

			void Value::SetDouble(double value)
			{
				if (!AllocateValue())
				{
					RemoveValue();
				}

				value_->double_v = value;
				type_ = ValueType::Double;
			}

			DataContainer& Value::CreateContainer()
			{
				if (!AllocateValue())
				{
					RemoveValue();
				}

				new (&value_->container_v) DataContainer();
				type_ = ValueType::Container;
				return value_->container_v;
			}

			DataContainer& Value::CreateContainer(const DataContainer& value)
			{
				if (!AllocateValue())
				{
					RemoveValue();
				}

				new (&value_->container_v) DataContainer(value);
				type_ = ValueType::Container;
				return value_->container_v;
			}

			DataContainer& Value::CreateContainer(DataContainer&& value)
			{
				if (!AllocateValue())
				{
					RemoveValue();
				}

				new (&value_->container_v) DataContainer(value);
				type_ = ValueType::Container;
				return value_->container_v;
			}

			std::vector<Value>& Value::CreateArray()
			{
				if (!AllocateValue())
				{
					RemoveValue();
				}

				new (&value_->array_v) std::vector<Value>();
				type_ = ValueType::Array;
				return value_->array_v;
			}

			std::vector<Value>& Value::CreateArray(const std::vector<Value>& value)
			{
				if (!AllocateValue())
				{
					RemoveValue();
				}

				new (&value_->array_v) std::vector<Value>(value);
				type_ = ValueType::Array;
				return value_->array_v;
			}

			std::vector<Value>& Value::CreateArray(std::vector<Value>&& value)
			{
				if (!AllocateValue())
				{
					RemoveValue();
				}
				
				new (&value_->array_v) std::vector<Value>(value);
				type_ = ValueType::Array;
				return value_->array_v;
			}

			inline void Value::RemoveValue()
			{
				switch (type_)
				{
				case ValueType::Array:
					value_->array_v.~vector();
					break;
				case ValueType::ByteString:
					value_->byte_string_v.~basic_string();
					break;
				case ValueType::Container:
					value_->container_v.~DataContainer();
					break;
				case ValueType::String:
					value_->string_v.~basic_string();
					break;
				}
			}

			inline bool Value::AllocateValue()
			{
				if (value_ == nullptr)
				{
					value_ = new ValueType_t();
					return true;
				}

				return false;
			}

			inline void Value::CopyUnion(const junjinjen_matrix::firmware::data_container::Value& other)
			{
				if (other.value_ != nullptr)
				{
					switch (other.type_)
					{
					case ValueType::Array:
						new (&value_->array_v) std::vector<Value>(other.value_->array_v);
						break;
					case ValueType::ByteString:
						new (&value_->byte_string_v) byte_string(other.value_->byte_string_v);
						break;
					case ValueType::Container:
						new (&value_->container_v) DataContainer(other.value_->container_v);
						break;
					case ValueType::String:
						new (&value_->string_v) std::string(other.value_->string_v);
						break;
					default:
						memcpy(value_, other.value_, sizeof(ValueType_t));
					}
				}
			}
		}
	}
}
