#include "CppUnitTest.h"
#include "Messaging/DataContainer/DataContainer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace junjinjen_matrix::firmware::messaging;

namespace MessagingUnitTests
{
	TEST_CLASS(ValueUnitTests)
	{
	public:
		TEST_METHOD(Empty_WhenValueIsEmpty_ReturnsTrue)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::IsTrue(value.Empty());
		}

		TEST_METHOD(Empty_WhenValueIsNotEmpty_ReturnsFalse)
		{
			// Arrange
			Value value(13);

			// Act / Assert
			Assert::IsFalse(value.Empty());
		}

		TEST_METHOD(IsInt32_WhenValueContainsInt32_ReturnsTrue)
		{
			// Arrange
			Value value(int32_t(12));

			// Act / Assert
			Assert::IsTrue(value.IsInt32());
		}

		TEST_METHOD(IsInt32_WhenValueDoesNotContainInt32_ReturnsFalse)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::IsFalse(value.IsInt32());
		}

		TEST_METHOD(IsInt64_WhenValueContainsInt64_ReturnsTrue)
		{
			// Arrange
			Value value(int64_t(12));

			// Act / Assert
			Assert::IsTrue(value.IsInt64());
		}

		TEST_METHOD(IsInt64_WhenValueDoesNotContainInt64_ReturnsFalse)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::IsFalse(value.IsInt64());
		}

		TEST_METHOD(IsBoolean_WhenValueContainsBoolean_ReturnsTrue)
		{
			// Arrange
			Value value(false);

			// Act / Assert
			Assert::IsTrue(value.IsBoolean());
		}

		TEST_METHOD(IsBoolean_WhenValueDoesNotContainBoolean_ReturnsFalse)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::IsFalse(value.IsBoolean());
		}

		TEST_METHOD(IsString_WhenValueContainsString_ReturnsTrue)
		{
			// Arrange
			Value value(std::string("Hello world"));

			// Act / Assert
			Assert::IsTrue(value.IsString());
		}

		TEST_METHOD(IsString_WhenValueDoesNotContainString_ReturnsFalse)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::IsFalse(value.IsString());
		}

		TEST_METHOD(IsByteString_WhenValueContainsByteString_ReturnsTrue)
		{
			// Arrange
			Value value(byte_string((const uint8_t*)"Hello world"));

			// Act / Assert
			Assert::IsTrue(value.IsByteString());
		}

		TEST_METHOD(IsByteString_WhenValueDoesNotContainByteString_ReturnsFalse)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::IsFalse(value.IsByteString());
		}

		TEST_METHOD(IsFloat_WhenValueContainsFloat_ReturnsTrue)
		{
			// Arrange
			Value value(float(14.34f));

			// Act / Assert
			Assert::IsTrue(value.IsFloat());
		}

		TEST_METHOD(IsFloat_WhenValueDoesNotContainFloat_ReturnsFalse)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::IsFalse(value.IsFloat());
		}

		TEST_METHOD(IsDouble_WhenValueContainsDouble_ReturnsTrue)
		{
			// Arrange
			Value value(double(14.34));

			// Act / Assert
			Assert::IsTrue(value.IsDouble());
		}

		TEST_METHOD(IsDouble_WhenValueDoesNotContainDouble_ReturnsFalse)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::IsFalse(value.IsDouble());
		}

		TEST_METHOD(IsArray_WhenValueContainsDouble_ReturnsTrue)
		{
			// Arrange
			std::vector<Value> array;
			Value value(array);

			// Act / Assert
			Assert::IsTrue(value.IsArray());
		}

		TEST_METHOD(IsArray_WhenValueDoesNotContainDouble_ReturnsFalse)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::IsFalse(value.IsArray());
		}

		TEST_METHOD(IsContainer_WhenValueContainsDouble_ReturnsTrue)
		{
			// Arrange
			DataContainer container;
			Value value(container);

			// Act / Assert
			Assert::IsTrue(value.IsContainer());
		}

		TEST_METHOD(IsContainer_WhenValueDoesNotContainDouble_ReturnsFalse)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::IsFalse(value.IsContainer());
		}

		TEST_METHOD(AsInt32_WhenValueContainsInt32_ReturnsTrue)
		{
			// Arrange
			int32_t expected = 14;
			Value value(expected);

			// Act / Assert
			Assert::AreEqual(expected, value.AsInt32());
		}

		TEST_METHOD(AsInt32_WhenValueIsEmpty_ThrowsInvalidType)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { value.AsInt32(); });
		}

		TEST_METHOD(AsInt32_WhenValueContainsInvalidType_ThrowsInvalidType)
		{
			// Arrange
			Value value(false);

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { value.AsInt32(); });
		}

		TEST_METHOD(AsInt64_WhenValueContainsInt64_ReturnsTrue)
		{
			// Arrange
			int64_t expected = 14;
			Value value(expected);

			// Act / Assert
			Assert::AreEqual(expected, value.AsInt64());
		}

		TEST_METHOD(AsInt64_WhenValueIsEmpty_ThrowsInvalidType)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { value.AsInt64(); });
		}

		TEST_METHOD(AsInt64_WhenValueContainsInvalidType_ThrowsInvalidType)
		{
			// Arrange
			Value value(false);

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { value.AsInt64(); });
		}

		TEST_METHOD(AsBoolean_WhenValueContainsBoolean_ReturnsTrue)
		{
			// Arrange
			bool expected = false;
			Value value(expected);

			// Act / Assert
			Assert::AreEqual(expected, value.AsBoolean());
		}

		TEST_METHOD(AsBoolean_WhenValueIsEmpty_ThrowsInvalidType)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { value.AsBoolean(); });
		}

		TEST_METHOD(AsBoolean_WhenValueContainsInvalidType_ThrowsInvalidType)
		{
			// Arrange
			Value value(14);

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { value.AsBoolean(); });
		}

		TEST_METHOD(AsString_WhenValueContainsString_ReturnsTrue)
		{
			// Arrange
			std::string expected = "Hello world";
			Value value(expected);

			// Act / Assert
			Assert::AreEqual(expected, value.AsString());
		}

		TEST_METHOD(AsString_WhenValueIsEmpty_ThrowsInvalidType)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { value.AsString(); });
		}

		TEST_METHOD(AsString_WhenValueContainsInvalidType_ThrowsInvalidType)
		{
			// Arrange
			Value value(false);

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { value.AsString(); });
		}

		TEST_METHOD(AsByteString_WhenValueContainsByteString_ReturnsTrue)
		{
			// Arrange
			byte_string expected = (const uint8_t*)"Hello world";
			Value value(expected);

			// Act / Assert
			Assert::AreEqual(reinterpret_cast<const char*>(&expected[0]), reinterpret_cast<const char*>(&value.AsByteString()[0]));
		}

		TEST_METHOD(AsByteString_WhenValueIsEmpty_ThrowsInvalidType)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { value.AsByteString(); });
		}

		TEST_METHOD(AsByteString_WhenValueContainsInvalidType_ThrowsInvalidType)
		{
			// Arrange
			Value value(14);

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { value.AsByteString(); });
		}

		TEST_METHOD(AsFloat_WhenValueContainsFloat_ReturnsTrue)
		{
			// Arrange
			float expected = 12.45f;
			Value value(expected);

			// Act / Assert
			Assert::AreEqual(expected, value.AsFloat());
		}

		TEST_METHOD(AsFloat_WhenValueIsEmpty_ThrowsInvalidType)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { value.AsFloat(); });
		}

		TEST_METHOD(AsFloat_WhenValueContainsInvalidType_ThrowsInvalidType)
		{
			// Arrange
			Value value(false);

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { value.AsFloat(); });
		}

		TEST_METHOD(AsDouble_WhenValueContainsDouble_ReturnsTrue)
		{
			// Arrange
			double expected = 12.45;
			Value value(expected);

			// Act / Assert
			Assert::AreEqual(expected, value.AsDouble());
		}

		TEST_METHOD(AsDouble_WhenValueIsEmpty_ThrowsInvalidType)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { value.AsDouble(); });
		}

		TEST_METHOD(AsDouble_WhenValueContainsInvalidType_ThrowsInvalidType)
		{
			// Arrange
			Value value(false);

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { value.AsDouble(); });
		}

		TEST_METHOD(Clear_WhenValueContainsValue_ClearsValue)
		{
			// Arrange
			Value value("Hello world");

			// Act
			value.Clear();

			// Assert
			Assert::IsTrue(value.Empty());
		}

		TEST_METHOD(Clear_WhenValueDoesNotContainValue_DoNothing)
		{
			// Arrange
			Value value;

			// Act
			value.Clear();

			// Assert
			Assert::IsTrue(value.Empty());
		}

		TEST_METHOD(SetInt32_WhenValueIsEmpty_InsertsValue)
		{
			// Arrange
			int32_t expected = 14;
			Value value;

			// Act
			value.SetInt32(expected);

			// Assert
			Assert::AreEqual(expected, value.AsInt32());
		}

		TEST_METHOD(SetInt32_WhenValueIsNotEmpty_UpdatesValue)
		{
			// Arrange
			int32_t expected = 14;
			Value value(false);

			// Act
			value.SetInt32(expected);

			// Assert
			Assert::AreEqual(expected, value.AsInt32());
		}

		TEST_METHOD(SetInt64_WhenValueIsEmpty_InsertsValue)
		{
			// Arrange
			int64_t expected = 14;
			Value value;

			// Act
			value.SetInt64(expected);

			// Assert
			Assert::AreEqual(expected, value.AsInt64());
		}

		TEST_METHOD(SetInt64_WhenValueIsNotEmpty_UpdatesValue)
		{
			// Arrange
			int64_t expected = 14;
			Value value(false);

			// Act
			value.SetInt64(expected);

			// Assert
			Assert::AreEqual(expected, value.AsInt64());
		}

		TEST_METHOD(SetBoolean_WhenValueIsEmpty_InsertsValue)
		{
			// Arrange
			bool expected = true;
			Value value;

			// Act
			value.SetBoolean(expected);

			// Assert
			Assert::AreEqual(expected, value.AsBoolean());
		}

		TEST_METHOD(SetBoolean_WhenValueIsNotEmpty_UpdatesValue)
		{
			// Arrange
			bool expected = true;
			Value value(14);

			// Act
			value.SetBoolean(expected);

			// Assert
			Assert::AreEqual(expected, value.AsBoolean());
		}

		TEST_METHOD(SetString_WhenValueIsEmpty_InsertsValue)
		{
			// Arrange
			std::string expected = "Hello world";
			Value value;

			// Act
			value.SetString(expected);

			// Assert
			Assert::AreEqual(expected, value.AsString());
		}

		TEST_METHOD(SetString_WhenValueIsNotEmpty_UpdatesValue)
		{
			// Arrange
			std::string expected = "Hello world";
			Value value(false);

			// Act
			value.SetString(expected);

			// Assert
			Assert::AreEqual(expected, value.AsString());
		}

		TEST_METHOD(SetStringByRValue_WhenValueIsEmpty_InsertsValue)
		{
			// Arrange
			std::string expected = "Hello world";
			Value value;

			// Act
			std::string expectedCopy = expected;
			value.SetString(std::move(expectedCopy));

			// Assert
			Assert::AreEqual(expected, value.AsString());
		}

		TEST_METHOD(SetStringByRValue_WhenValueIsNotEmpty_UpdatesValue)
		{
			// Arrange
			std::string expected = "Hello world";
			Value value(14);

			// Act
			std::string expectedCopy = expected;
			value.SetString(std::move(expectedCopy));

			// Assert
			Assert::AreEqual(expected, value.AsString());
		}

		TEST_METHOD(SetByteString_WhenValueIsEmpty_InsertsValue)
		{
			// Arrange
			byte_string expected = (const uint8_t*)"Hello world";
			Value value;

			// Act
			value.SetByteString(expected);

			// Assert
			Assert::AreEqual(reinterpret_cast<const char*>(&expected[0]), reinterpret_cast<const char*>(&value.AsByteString()[0]));
		}

		TEST_METHOD(SetByteString_WhenValueIsNotEmpty_UpdatesValue)
		{
			// Arrange
			byte_string expected = (const uint8_t*)"Hello world";
			Value value(false);

			// Act
			value.SetByteString(expected);

			// Assert
			Assert::AreEqual(reinterpret_cast<const char*>(&expected[0]), reinterpret_cast<const char*>(&value.AsByteString()[0]));
		}

		TEST_METHOD(SetByteStringByRValue_WhenValueIsEmpty_InsertsValue)
		{
			// Arrange
			byte_string expected = (const uint8_t*)"Hello world";
			Value value;

			// Act
			byte_string expectedCopy = expected;
			value.SetByteString(std::move(expectedCopy));

			// Assert
			Assert::AreEqual(reinterpret_cast<const char*>(&expected[0]), reinterpret_cast<const char*>(&value.AsByteString()[0]));
		}

		TEST_METHOD(SetByteStringByRValue_WhenValueIsNotEmpty_UpdatesValue)
		{
			// Arrange
			byte_string expected = (const uint8_t*)"Hello world";
			Value value(false);

			// Act
			byte_string expectedCopy = expected;
			value.SetByteString(std::move(expectedCopy));

			// Assert
			Assert::AreEqual(reinterpret_cast<const char*>(&expected[0]), reinterpret_cast<const char*>(&value.AsByteString()[0]));
		}

		TEST_METHOD(SetFloat_WhenValueIsEmpty_InsertsValue)
		{
			// Arrange
			float expected = 13.5f;
			Value value;

			// Act
			value.SetFloat(expected);

			// Assert
			Assert::AreEqual(expected, value.AsFloat());
		}

		TEST_METHOD(SetFloat_WhenValueIsNotEmpty_UpdatesValue)
		{
			// Arrange
			float expected = 13.5f;
			Value value(false);

			// Act
			value.SetFloat(expected);

			// Assert
			Assert::AreEqual(expected, value.AsFloat());
		}

		TEST_METHOD(SetDouble_WhenValueIsEmpty_InsertsValue)
		{
			// Arrange
			double expected = 13.5;
			Value value;

			// Act
			value.SetDouble(expected);

			// Assert
			Assert::AreEqual(expected, value.AsDouble());
		}

		TEST_METHOD(SetDouble_WhenValueIsNotEmpty_UpdatesValue)
		{
			// Arrange
			double expected = 13.5;
			Value value(false);

			// Act
			value.SetDouble(expected);

			// Assert
			Assert::AreEqual(expected, value.AsDouble());
		}

		TEST_METHOD(AsContainer_WhenValueContainsContainer_ReturnsTrue)
		{
			// Arrange
			DataContainer expected;
			std::string key = "tmp";
			std::string str = "Hello world";
			expected.SetString(key, str);

			Value value(expected);

			// Act / Assert
			Assert::IsTrue(expected == value.AsContainer());
		}

		TEST_METHOD(AsContainer_WhenValueIsEmpty_ThrowsInvalidType)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { value.AsContainer(); });
		}

		TEST_METHOD(AsContainer_WhenValueContainsInvalidType_ThrowsInvalidType)
		{
			// Arrange
			Value value(false);

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { value.AsContainer(); });
		}

		TEST_METHOD(AsContainerConst_WhenValueContainsContainer_ReturnsTrue)
		{
			// Arrange
			DataContainer expected;
			std::string key = "tmp";
			std::string str = "Hello world";
			expected.SetString(key, str);

			Value value(expected);
			const Value& constValue = value;

			// Act / Assert
			Assert::IsTrue(expected == constValue.AsContainer());
		}

		TEST_METHOD(AsContainerConst_WhenValueIsEmpty_ThrowsInvalidType)
		{
			// Arrange
			Value value;
			const Value& constValue = value;

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { constValue.AsContainer(); });
		}

		TEST_METHOD(AsContainerConst_WhenValueContainsInvalidType_ThrowsInvalidType)
		{
			// Arrange
			Value value(false);
			const Value& constValue = value;

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { constValue.AsContainer(); });
		}

		TEST_METHOD(AsArray_WhenValueContainsArray_ReturnsTrue)
		{
			// Arrange
			std::vector<Value> expected;
			std::string str1 = "Hello";
			std::string str2 = "World";
			expected.push_back(str1);
			expected.push_back(str2);

			Value value(expected);

			// Act / Assert
			Assert::IsTrue(expected == value.AsArray());
		}

		TEST_METHOD(AsArray_WhenValueIsEmpty_ThrowsInvalidType)
		{
			// Arrange
			Value value;

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { value.AsArray(); });
		}

		TEST_METHOD(AsArray_WhenValueContainsInvalidType_ThrowsInvalidType)
		{
			// Arrange
			Value value(false);

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { value.AsArray(); });
		}

		TEST_METHOD(AsArrayConst_WhenValueContainsArray_ReturnsTrue)
		{
			// Arrange
			std::vector<Value> expected;
			std::string str1 = "Hello";
			std::string str2 = "World";
			expected.push_back(str1);
			expected.push_back(str2);

			Value value(expected);
			const Value& constValue = value;

			// Act / Assert
			Assert::IsTrue(expected == constValue.AsArray());
		}

		TEST_METHOD(AsArrayConst_WhenValueIsEmpty_ThrowsInvalidType)
		{
			// Arrange
			Value value;
			const Value& constValue = value;

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { constValue.AsArray(); });
		}

		TEST_METHOD(AsArrayConst_WhenValueContainsInvalidType_ThrowsInvalidType)
		{
			// Arrange
			Value value(false);
			const Value& constValue = value;

			// Act / Assert
			Assert::ExpectException<InvalidTypeException>([&]() { constValue.AsArray(); });
		}

		TEST_METHOD(CreateContainer_WhenValueIsEmpty_ReturnsCreatedContainer)
		{
			// Arrange
			Value value;

			// Act
			auto& container = value.CreateContainer();

			// Assert
			Assert::IsTrue(value.IsContainer());
			Assert::IsTrue(container.Empty());
		}

		TEST_METHOD(CreateContainer_WhenValueIsNotEmpty_ReturnsCreatedContainer)
		{
			// Arrange
			Value value(true);

			// Act
			auto& container = value.CreateContainer();

			// Assert
			Assert::IsTrue(value.IsContainer());
			Assert::IsTrue(container.Empty());
		}

		TEST_METHOD(CreateContainerByLValue_WhenValueIsEmpty_ReturnsCreatedContainer)
		{
			// Arrange
			Value value;

			std::string key = "tmp";
			std::string str = "Hello world";
			DataContainer container;
			container.SetString(key, str);

			// Act
			auto& node = value.CreateContainer(container);

			// Assert
			Assert::IsTrue(value.IsContainer());
			Assert::AreEqual(str, node.GetString(key));
		}

		TEST_METHOD(CreateContainerByLValue_WhenValueIsNotEmpty_ReturnsCreatedContainer)
		{
			// Arrange
			Value value(true);

			std::string key = "tmp";
			std::string str = "Hello world";
			DataContainer container;
			container.SetString(key, str);

			// Act
			auto& node = value.CreateContainer(container);

			// Assert
			Assert::IsTrue(value.IsContainer());
			Assert::AreEqual(str, node.GetString(key));
		}

		TEST_METHOD(CreateContainerByRValue_WhenValueIsEmpty_ReturnsCreatedContainer)
		{
			// Arrange
			Value value;

			std::string key = "tmp";
			std::string str = "Hello world";
			DataContainer container;
			container.SetString(key, str);

			// Act
			auto& node = value.CreateContainer(std::move(container));

			// Assert
			Assert::IsTrue(value.IsContainer());
			Assert::AreEqual(str, node.GetString(key));
		}

		TEST_METHOD(CreateContainerByRValue_WhenValueIsNotEmpty_ReturnsCreatedContainer)
		{
			// Arrange
			Value value(true);

			std::string key = "tmp";
			std::string str = "Hello world";
			DataContainer container;
			container.SetString(key, str);

			// Act
			auto& node = value.CreateContainer(std::move(container));

			// Assert
			Assert::IsTrue(value.IsContainer());
			Assert::AreEqual(str, node.GetString(key));
		}

		TEST_METHOD(CreateArray_WhenValueIsEmpty_ReturnsCreatedArray)
		{
			// Arrange
			Value value;

			// Act
			auto& arrayValue = value.CreateArray();

			// Assert
			Assert::IsTrue(value.IsArray());
			Assert::IsTrue(arrayValue.empty());
		}

		TEST_METHOD(CreateArray_WhenValueIsNotEmpty_ReturnsCreatedArray)
		{
			// Arrange
			Value value(true);

			// Act
			auto& arrayValue = value.CreateArray();

			// Assert
			Assert::IsTrue(value.IsArray());
			Assert::IsTrue(arrayValue.empty());
		}

		TEST_METHOD(CreateArrayByLValue_WhenValueIsEmpty_ReturnsCreatedArray)
		{
			// Arrange
			Value value;

			std::vector<Value> array;
			std::string str1 = "Hello";
			std::string str2 = "World";
			array.push_back(str1);
			array.push_back(str2);

			// Act
			auto& node = value.CreateArray(array);

			// Assert
			Assert::IsTrue(value.IsArray());
			Assert::IsTrue(array == node);
		}

		TEST_METHOD(CreateArrayByLValue_WhenValueIsNotEmpty_ReturnsCreatedArray)
		{
			// Arrange
			Value value(true);

			std::vector<Value> array;
			std::string str1 = "Hello";
			std::string str2 = "World";
			array.push_back(str1);
			array.push_back(str2);

			// Act
			auto& node = value.CreateArray(array);

			// Assert
			Assert::IsTrue(value.IsArray());
			Assert::IsTrue(array == node);
		}

		TEST_METHOD(CreateArrayByRValue_WhenValueIsEmpty_ReturnsCreatedArray)
		{
			// Arrange
			Value value;

			std::vector<Value> array;
			std::string str1 = "Hello";
			std::string str2 = "World";
			array.push_back(str1);
			array.push_back(str2);

			// Act
			std::vector<Value> arrayCopy = array;
			auto& node = value.CreateArray(std::move(arrayCopy));

			// Assert
			Assert::IsTrue(value.IsArray());
			Assert::IsTrue(array == node);
		}

		TEST_METHOD(CreateArrayByRValue_WhenValueIsNotEmpty_ReturnsCreatedArray)
		{
			// Arrange
			Value value(true);

			std::vector<Value> array;
			std::string str1 = "Hello";
			std::string str2 = "World";
			array.push_back(str1);
			array.push_back(str2);

			// Act
			std::vector<Value> arrayCopy = array;
			auto& node = value.CreateArray(std::move(arrayCopy));

			// Assert
			Assert::IsTrue(value.IsArray());
			Assert::IsTrue(array == node);
		}
	};
}