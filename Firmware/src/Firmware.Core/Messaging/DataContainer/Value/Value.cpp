#include "Value.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace messaging
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

			Value::Value(Value&& value) noexcept
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
				new (&value_->string_v) std::string(std::move(value));
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
				new (&value_->byte_string_v) byte_string(std::move(value));
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

			Value::Value(DataContainer&& value)
			{
				value_ = new ValueType_t();
				new (&value_->container_v) DataContainer(std::move(value));
				type_ = ValueType::Container;
			}

			Value::Value(const std::vector<Value>& value)
			{
				value_ = new ValueType_t();
				new (&value_->array_v) std::vector<Value>(value);
				type_ = ValueType::Array;
			}

			Value::Value(std::vector<Value>&& value)
			{
				value_ = new ValueType_t();
				new (&value_->array_v) std::vector<Value>(std::move(value));
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

			void Value::operator=(Value&& value) noexcept
			{
				if (value_ != nullptr)
				{
					RemoveValue();
				}
				
				type_ = value.type_;
				value_ = value.value_;

				value.type_ = ValueType::Empty;
				value.value_ = nullptr;
			}

			bool Value::operator==(const Value& other) const
			{
				if (type_ != other.type_)
				{
					return false;
				}

				switch (type_)
				{
				case ValueType::Empty:
					return true;
				case ValueType::Int32:
					return value_->int32_v == other.value_->int32_v;
					break;
				case ValueType::Int64:
					return value_->int64_v == other.value_->int64_v;
					break;
				case ValueType::Boolean:
					return value_->bool_v == other.value_->bool_v;
					break;
				case ValueType::String:
					return value_->string_v == other.value_->string_v;
					break;
				case ValueType::ByteString:
					return value_->byte_string_v == other.value_->byte_string_v;
					break;
				case ValueType::Float:
					return value_->float_v == other.value_->float_v;
					break;
				case ValueType::Double:
					return value_->double_v == other.value_->double_v;
					break;
				case ValueType::Container:
					return value_->container_v == other.value_->container_v;
					break;
				case ValueType::Array:
					return value_->array_v == other.value_->array_v;
					break;
				}

				return false;
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

			int32_t Value::AsInt32() const
			{
				if (!IsInt32())
				{
					throw InvalidTypeException();
				}

				return value_->int32_v;
			}

			int64_t Value::AsInt64() const
			{
				if (!IsInt64())
				{
					throw InvalidTypeException();
				}

				return value_->int64_v;
			}

			bool Value::AsBoolean() const
			{
				if (!IsBoolean())
				{
					throw InvalidTypeException();
				}

				return value_->bool_v;
			}

			const std::string& Value::AsString() const
			{
				if (!IsString())
				{
					throw InvalidTypeException();
				}

				return value_->string_v;
			}

			const byte_string& Value::AsByteString() const
			{
				if (!IsByteString())
				{
					throw InvalidTypeException();
				}

				return value_->byte_string_v;
			}

			float Value::AsFloat() const
			{
				if (!IsFloat())
				{
					throw InvalidTypeException();
				}

				return value_->float_v;
			}

			double Value::AsDouble() const
			{
				if (!IsDouble())
				{
					throw InvalidTypeException();
				}

				return value_->double_v;
			}

			DataContainer& Value::AsContainer()
			{
				return const_cast<DataContainer&>(const_cast<const Value*>(this)->AsContainer());
			}

			const DataContainer& Value::AsContainer() const
			{
				if (!IsContainer())
				{
					throw InvalidTypeException();
				}

				return value_->container_v;
			}

			std::vector<Value>& Value::AsArray()
			{
				return const_cast<std::vector<Value>&>(const_cast<const Value*>(this)->AsArray());
			}

			const std::vector<Value>& Value::AsArray() const
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

				new (&value_->string_v) std::string(std::move(value));
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

				new (&value_->byte_string_v) byte_string(std::move(value));
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

				new (&value_->container_v) DataContainer(std::move(value));
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
				
				new (&value_->array_v) std::vector<Value>(std::move(value));
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

			inline void Value::CopyUnion(const junjinjen_matrix::firmware::messaging::Value& other)
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
