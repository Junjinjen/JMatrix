#include "Value/Value.h"
#include "DataContainer.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace data_container
		{
			bool DataContainer::Empty() const
			{
				return values_.empty();
			}

			bool DataContainer::HasValue(const std::string& key) const
			{
				for (size_t i = 0; i < values_.size(); i++)
				{
					if (values_[i].first == key)
					{
						return true;
					}
				}

				return false;
			}

			void DataContainer::SetValue(const std::string& key, const Value& value)
			{
				for (size_t i = 0; i < values_.size(); i++)
				{
					if (values_[i].first == key)
					{
						values_[i].second = value;
						return;
					}
				}

				values_.emplace_back(key, value);
			}

			Value& DataContainer::GetValue(const std::string& key)
			{
				Value* ptr = FindValue(key);
				if (ptr != nullptr)
				{
					return *ptr;
				}

				throw std::out_of_range("Value with name " + key + " wasn't found");
			}

			Value& DataContainer::operator[](const std::string& key)
			{
				Value* ptr = FindValue(key);
				if (ptr != nullptr)
				{
					return *ptr;
				}

				values_.emplace_back(key, Value());
				return values_.back().second;
			}

			void DataContainer::SetInt32(const std::string& key, int32_t value)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					node->SetInt32(value);
				}
				else
				{
					values_.emplace_back(key, Value(value));
				}
			}

			void DataContainer::SetInt64(const std::string& key, int64_t value)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					node->SetInt64(value);
				}
				else
				{
					values_.emplace_back(key, Value(value));
				}
			}

			void DataContainer::SetBoolean(const std::string& key, bool value)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					node->SetBoolean(value);
				}
				else
				{
					values_.emplace_back(key, Value(value));
				}
			}

			void DataContainer::SetString(const std::string& key, const std::string& value)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					node->SetString(value);
				}
				else
				{
					values_.emplace_back(key, Value(value));
				}
			}

			void DataContainer::SetString(const std::string& key, std::string&& value)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					node->SetString(std::move(value));
				}
				else
				{
					values_.emplace_back(key, Value(value));
				}
			}

			void DataContainer::SetByteString(const std::string& key, const byte_string& value)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					node->SetByteString(value);
				}
				else
				{
					values_.emplace_back(key, Value(value));
				}
			}

			void DataContainer::SetByteString(const std::string& key, byte_string&& value)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					node->SetByteString(value);
				}
				else
				{
					values_.emplace_back(key, Value(std::move(value)));
				}
			}

			void DataContainer::SetFloat(const std::string& key, float value)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					node->SetFloat(value);
				}
				else
				{
					values_.emplace_back(key, Value(value));
				}
			}

			void DataContainer::SetDouble(const std::string& key, double value)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					node->SetDouble(value);
				}
				else
				{
					values_.emplace_back(key, Value(value));
				}
			}

			int32_t DataContainer::GetInt32(const std::string& key)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					return node->GetInt32();
				}

				throw std::out_of_range("Value with name " + key + " wasn't found");
			}

			int64_t DataContainer::GetInt64(const std::string& key)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					return node->GetInt64();
				}

				throw std::out_of_range("Value with name " + key + " wasn't found");
			}

			bool DataContainer::GetBoolean(const std::string& key)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					return node->GetBoolean();
				}

				throw std::out_of_range("Value with name " + key + " wasn't found");
			}

			const std::string& DataContainer::GetString(const std::string& key)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					return node->GetString();
				}

				throw std::out_of_range("Value with name " + key + " wasn't found");
			}

			const byte_string& DataContainer::GetByteString(const std::string& key)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					return node->GetByteString();
				}

				throw std::out_of_range("Value with name " + key + " wasn't found");
			}

			float DataContainer::GetFloat(const std::string& key)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					return node->GetFloat();
				}

				throw std::out_of_range("Value with name " + key + " wasn't found");
			}

			double DataContainer::GetDouble(const std::string& key)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					return node->GetDouble();
				}

				throw std::out_of_range("Value with name " + key + " wasn't found");
			}

			DataContainer& DataContainer::SetContainer(const std::string& key)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					return node->CreateContainer();
				}

				values_.emplace_back(key, Value());
				return values_.back().second.CreateContainer();
			}

			void DataContainer::SetContainer(const std::string& key, const DataContainer& value)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					node->CreateContainer(value);
				}

				values_.emplace_back(key, Value());
				values_.back().second.CreateContainer(value);
			}

			void DataContainer::SetContainer(const std::string& key, DataContainer&& value)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					node->CreateContainer(std::move(value));
				}

				values_.emplace_back(key, Value());
				values_.back().second.CreateContainer(std::move(value));
			}

			DataContainer& DataContainer::GetContainer(const std::string& key)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					return node->AsContainer();
				}

				throw std::out_of_range("Container with name " + key + " wasn't found");
			}

			std::vector<Value>& DataContainer::SetArray(const std::string& key)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					return node->CreateArray();
				}

				values_.emplace_back(key, Value());
				return values_.back().second.CreateArray();
			}

			void DataContainer::SetArray(const std::string& key, const std::vector<Value>& value)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					node->CreateArray(value);
				}

				values_.emplace_back(key, Value());
				values_.back().second.CreateArray(value);
			}

			void DataContainer::SetArray(const std::string& key, std::vector<Value>&& value)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					node->CreateArray(std::move(value));
				}

				values_.emplace_back(key, Value());
				values_.back().second.CreateArray(std::move(value));
			}

			std::vector<Value>& DataContainer::GetArray(const std::string& key)
			{
				Value* node = FindValue(key);
				if (node != nullptr)
				{
					return node->AsArray();
				}

				throw std::out_of_range("Array with name " + key + " wasn't found");
			}

			Value* DataContainer::FindValue(const std::string& key)
			{
				for (size_t i = 0; i < values_.size(); i++)
				{
					if (values_[i].first == key)
					{
						return &values_[i].second;
					}
				}

				return nullptr;
			}
		}
	}
}
