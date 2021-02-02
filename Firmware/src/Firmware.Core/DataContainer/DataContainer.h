#pragma once
#include "Utilities/ByteDefinitions/ByteDefinitions.h"
#include <vector>
#include <utility>
#include <string>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace data_container
		{
			using utilities::byte_definitions::byte_string;

			class Value;

			class DataContainer
			{
			public:
				bool Empty() const;
				bool HasValue(const std::string& key) const;

				void SetValue(const std::string& key, const Value& value);
				Value& GetValue(const std::string& key);
				Value& operator[](const std::string& key);

				void SetInt32(const std::string& key, int32_t value);
				void SetInt64(const std::string& key, int64_t value);
				void SetBoolean(const std::string& key, bool value);
				void SetString(const std::string& key, const std::string& value);
				void SetString(const std::string& key, std::string&& value);
				void SetByteString(const std::string& key, const byte_string& value);
				void SetByteString(const std::string& key, byte_string&& value);
				void SetFloat(const std::string& key, float value);
				void SetDouble(const std::string& key, double value);

				int32_t GetInt32(const std::string& key);
				int64_t GetInt64(const std::string& key);
				bool GetBoolean(const std::string& key);
				const std::string& GetString(const std::string& key);
				const byte_string& GetByteString(const std::string& key);
				float GetFloat(const std::string& key);
				double GetDouble(const std::string& key);

				DataContainer& SetContainer(const std::string& key);
				void SetContainer(const std::string& key, const DataContainer& value);
				void SetContainer(const std::string& key, DataContainer&& value);
				DataContainer& GetContainer(const std::string& key);

				std::vector<Value>& SetArray(const std::string& key);
				void SetArray(const std::string& key, const std::vector<Value>& value);
				void SetArray(const std::string& key, std::vector<Value>&& value);
				std::vector<Value>& GetArray(const std::string& key);
			private:
				std::vector<std::pair<std::string, Value>> values_;

				Value* FindValue(const std::string& key);
			};
		}
	}
}