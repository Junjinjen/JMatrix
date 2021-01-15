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
			byte_string network;

			{
				int number = 13;
				std::string string = "Hello world!";
				bool boolean = true;
				std::vector<float> vec{ 1,3,5 };
				std::vector<std::string> strVec{ "Hello", "this", "is", "amazing" };

				SerializableObject a;
				a.TrySetValue("Num", number);
				a.TrySetValue("Str", string);
				a.TrySetValue("Bool", boolean);
				a.TrySetArray("Vec", vec);

				SerializableObject b;
				b.TrySetArray("StrVec", strVec);
				b.TrySetValue("Obj", a);

				network = b.Serialize();
			}

			{
				int number_n;
				std::string string_n;
				bool boolean_n;
				std::vector<float> vec_n;
				std::vector<std::string> strVec_n;

				SerializableObject b_n;
				SerializableObject a_n;

				b_n.Deserialize(network);
				b_n.TryGetArray("StrVec", strVec_n);
				b_n.TryGetValue("Obj", a_n);

				a_n.TryGetValue("Num", number_n);
				a_n.TryGetValue("Str", string_n);
				a_n.TryGetValue("Bool", boolean_n);
				a_n.TryGetArray("Vec", vec_n);
			}
		}
	};
}