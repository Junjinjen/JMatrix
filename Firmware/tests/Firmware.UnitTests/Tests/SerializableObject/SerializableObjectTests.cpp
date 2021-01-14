#include "CppUnitTest.h"
#include "Utilities/SerializableObject/SerializableObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace junjinjen_matrix::firmware::utilities::serializable_object::converters;
using namespace junjinjen_matrix::firmware::utilities::serializable_object;

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
			SerializableObject a;

			a.TrySetValue("Int", 13);
			char* ty = (char*)"Hello world";
			a.TrySetValue("String", ty);

			int bbb;
			std::string ccc;
			a.TryGetValue("Int", bbb);
			a.TryGetValue("String", ccc);
		}
	};
}