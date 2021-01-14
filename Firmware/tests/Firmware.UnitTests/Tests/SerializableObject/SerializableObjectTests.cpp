#include "CppUnitTest.h"
#include "Utilities/SerializableObject/Converters/ValueConverter/ValueConverter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace junjinjen_matrix::firmware::utilities::serializable_object::converters;

namespace JunjinjenMatrixUnitTests
{
	class MyClass : public Serializable
	{
	public:
		// Inherited via Serializable
		virtual bool Serialize(std::basic_ostream<uint8_t>& stream) const override
		{
			stream.write((uint8_t*)&a, sizeof(int));
			stream.write((uint8_t*)&b, sizeof(bool));
			return stream.good();
		}

		virtual bool Deserialize(std::basic_istream<uint8_t>& stream) override
		{
			stream.read((uint8_t*)&a, sizeof(int));
			stream.read((uint8_t*)&b, sizeof(bool));
			return stream.good();
		}

		int a;
		bool b;
	};

	TEST_CLASS(SerializableObjectUnitTests)
	{
	public:
		TEST_METHOD(HasNewTasks_WhenPipeManagerHasNewPipeWithMessage_ReturnsTrue)
		{
			ValueConverter<std::string> a;
			std::string tt = "Hello world";

			std::basic_stringstream<uint8_t> ss;
			a.TrySetValue(ss, tt);

			std::string tta;
			a.TryGetValue(ss, tta);
		}
	};
}