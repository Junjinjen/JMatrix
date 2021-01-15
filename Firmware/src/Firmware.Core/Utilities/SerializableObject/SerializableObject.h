#pragma once
#include "Utilities/SerializableObject/Container/Container.h"
#include "Utilities/SerializableObject/SerializableInterface/Serializable.h"
#include "Utilities/SerializableObject/Converters/ArrayConverter/ArrayConverter.h"
#include <map>

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace utilities
		{
			namespace serializable_object
			{
				using utilities::byte_string::byte_string;
				using serializable_interface::Serializable;
				using container::Container;
				using converters::ArrayConverter;
				using converters::ValueConverter;

				class SerializableObject : public Serializable
				{
				public:
					byte_string Serialize() const;
					bool Deserialize(const byte_string& string);

					virtual bool Serialize(std::basic_ostream<uint8_t>& stream) const override;
					virtual bool Deserialize(std::basic_istream<uint8_t>& stream) override;

					std::vector<std::string> GetNames() const;
					bool HasValue(const std::string& name) const;

					template<typename T>
					bool TrySetValue(const std::string& name, T& value)
					{
						ValueConverter<T> converter;
						Container container = GetOrCreateContainerByName(name);
						std::basic_ostringstream<uint8_t> stream;
						if (converter.TrySetValue(stream, value))
						{
							container.SetData(std::move(stream.str()));
							elements_.push_back(container);
							return true;
						}

						return false;
					}

					template<typename = const char*>
					bool TrySetValue(const std::string& name, const char* value)
					{
						ValueConverter<const char*> converter;
						Container container = GetOrCreateContainerByName(name);
						std::basic_ostringstream<uint8_t> stream;
						if (converter.TrySetValue(stream, value))
						{
							container.SetData(std::move(stream.str()));
							elements_.push_back(container);
							return true;
						}

						return false;
					}

					template<typename T>
					bool TryGetValue(const std::string& name, T& value)
					{
						ValueConverter<T> converter;
						Container* container = GetContainerByName(name);
						if (container != nullptr)
						{
							const byte_string& str = container->GetData();
							std::basic_istringstream<uint8_t> stream(str);
							return converter.TryGetValue(stream, value) && stream.tellg() == str.size();
						}

						return false;
					}

					template<typename T>
					bool TrySetArray(const std::string& name, const T* values, size_t count)
					{
						ArrayConverter<T> converter;
						Container container = GetOrCreateContainerByName(name);

						std::basic_ostringstream<uint8_t> stream;
						if (converter.TrySetArray(stream, values, count))
						{
							container.SetData(std::move(stream.str()));
							elements_.push_back(container);
							return true;
						}

						return false;
					}

					template<typename T>
					bool TrySetArray(const std::string& name, const std::vector<T>& values)
					{
						ArrayConverter<T> converter;
						Container container = GetOrCreateContainerByName(name);

						std::basic_ostringstream<uint8_t> stream;
						if (converter.TrySetArray(stream, values))
						{
							container.SetData(std::move(stream.str()));
							elements_.push_back(container);
							return true;
						}

						return false;
					}

					template<typename T>
					bool TryGetArray(const std::string& name, std::vector<T>& values)
					{
						ArrayConverter<T> converter;
						Container* container = GetContainerByName(name);
						if (container != nullptr)
						{
							const byte_string& str = container->GetData();
							std::basic_istringstream<uint8_t> stream(str);
							return converter.TryGetArray(stream, values) && stream.tellg() == str.size();
						}

						return false;
					}
				private:
					ArrayConverter<Container> elementsConverter_;
					std::vector<Container> elements_;

					Container GetOrCreateContainerByName(const std::string& name);
					Container* GetContainerByName(const std::string& name);
				};
			}
		}
	}
}
