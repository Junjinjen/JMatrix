#include "CppUnitTest.h"
#include "Messaging/DataContainer/DataContainer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace junjinjen_matrix::firmware::messaging;

namespace MessagingTests
{
	TEST_CLASS(DataContainerTests)
	{
		TEST_METHOD(Empty_WhenContainerIsEmpty_ReturnsTrue)
		{
			// Arrange
			DataContainer container;

			// Act / Assert
			Assert::IsTrue(container.Empty());
		}

		TEST_METHOD(Empty_WhenContainerHasValue_ReturnsFalse)
		{
			// Arrange
			DataContainer container;
			container.SetBoolean("tmp", true);

			// Act / Assert
			Assert::IsFalse(container.Empty());
		}

		TEST_METHOD(HasValue_WhenContainerHasValue_ReturnsTrue)
		{
			// Arrange
			DataContainer container;
			container.SetBoolean("tmp", true);

			// Act / Assert
			Assert::IsTrue(container.HasValue("tmp"));
		}

		TEST_METHOD(HasValue_WhenContainerHasNotValue_ReturnsFalse)
		{
			// Arrange
			DataContainer container;
			container.SetBoolean("nottmp", true);

			// Act / Assert
			Assert::IsFalse(container.HasValue("tmp"));
		}

		TEST_METHOD(SetValue_WhenContainerHasValueWithGivenKey_UpdatesValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldData = "Test value";
			std::string expected = "New test value";
			container.SetValue(key, Value(oldData));

			// Act
			container.SetValue(key, Value(expected));

			// Assert
			Assert::IsTrue(container.HasValue(key));
			Assert::AreEqual(expected, container.GetString(key));
		}

		TEST_METHOD(SetValue_WhenContainerHasNotValueWithGivenKey_CreatesValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string expected = "Test value";

			// Act
			container.SetValue(key, Value(expected));

			// Assert
			Assert::AreEqual(expected, container.GetString(key));
		}

		TEST_METHOD(GetValue_WhenContainerHasNotValueWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetValue(key); });
		}

		TEST_METHOD(GetValue_WhenContainerHasValueWithGivenKey_ReturnsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string expected = "Test value";
			container.SetValue(key, Value(expected));
			
			// Act
			const auto& value = container.GetValue(key);

			// Assert 
			Assert::AreEqual(expected, value.AsString());
		}

		TEST_METHOD(GetValueConst_WhenContainerHasNotValueWithGivenKey_AssertFailed)
		{
			// Arrange
			const DataContainer container;
			std::string key = "tmp";

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetValue(key); });
		}

		TEST_METHOD(GetValueConst_WhenContainerHasValueWithGivenKey_ReturnsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string expected = "Test value";
			container.SetValue(key, Value(expected));
			const DataContainer& constInstance = container;

			// Act
			const auto& value = constInstance.GetValue(key);

			// Assert 
			Assert::AreEqual(expected, value.AsString());
		}

		TEST_METHOD(Indexator_WhenContainerHasValueWithGivenKey_ReturnsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string expected = "Test value";
			container.SetValue(key, Value(expected));

			// Act
			const auto& value = container[key];

			// Assert 
			Assert::AreEqual(expected, value.AsString());
		}

		TEST_METHOD(SetInt32_WhenContainerHasValueWithGivenKey_UpdatesValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			int32_t expected = 14;
			container.SetString(key, oldValue);

			// Act
			container.SetInt32(key, expected);

			// Assert
			Assert::AreEqual(expected, container.GetInt32(key));
		}

		TEST_METHOD(SetInt32_WhenContainerHasNotValueWithGivenKey_InsertsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			int32_t expected = 14;

			// Act
			container.SetInt32(key, expected);

			// Assert
			Assert::AreEqual(expected, container.GetInt32(key));
		}

		TEST_METHOD(SetInt64_WhenContainerHasValueWithGivenKey_UpdatesValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			int64_t expected = 14;
			container.SetString(key, oldValue);

			// Act
			container.SetInt64(key, expected);

			// Assert
			Assert::AreEqual(expected, container.GetInt64(key));
		}

		TEST_METHOD(SetInt64_WhenContainerHasNotValueWithGivenKey_InsertsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			int64_t expected = 14;

			// Act
			container.SetInt64(key, expected);

			// Assert
			Assert::AreEqual(expected, container.GetInt64(key));
		}

		TEST_METHOD(SetBoolean_WhenContainerHasValueWithGivenKey_UpdatesValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			bool expected = false;
			container.SetString(key, oldValue);

			// Act
			container.SetBoolean(key, expected);

			// Assert
			Assert::AreEqual(expected, container.GetBoolean(key));
		}

		TEST_METHOD(SetBoolean_WhenContainerHasNotValueWithGivenKey_InsertsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			bool expected = true;

			// Act
			container.SetBoolean(key, expected);

			// Assert
			Assert::AreEqual(expected, container.GetBoolean(key));
		}

		TEST_METHOD(SetString_WhenContainerHasValueWithGivenKey_UpdatesValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			std::string expected = "Hello world!";
			container.SetString(key, oldValue);

			// Act
			container.SetString(key, expected);

			// Assert
			Assert::AreEqual(expected, container.GetString(key));
		}

		TEST_METHOD(SetString_WhenContainerHasNotValueWithGivenKey_InsertsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string expected = "Bye world";

			// Act
			container.SetString(key, expected);

			// Assert
			Assert::AreEqual(expected, container.GetString(key));
		}

		TEST_METHOD(SetStringByRValue_WhenContainerHasValueWithGivenKey_UpdatesValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			std::string expected = "Hello world";
			container.SetString(key, oldValue);

			// Act
			std::string expectedCopy = expected;
			container.SetString(key, std::move(expectedCopy));

			// Assert
			Assert::AreEqual(expected, container.GetString(key));
		}

		TEST_METHOD(SetStringByRValue_WhenContainerHasNotValueWithGivenKey_InsertsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string expected = "Hello world";

			// Act
			std::string expectedCopy = expected;
			container.SetString(key, std::move(expectedCopy));

			// Assert
			Assert::AreEqual(expected, container.GetString(key));
		}

		TEST_METHOD(SetByteString_WhenContainerHasValueWithGivenKey_UpdatesValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			byte_string expected = (const uint8_t*)"Hello world!";
			container.SetString(key, oldValue);

			// Act
			container.SetByteString(key, expected);

			// Assert
			Assert::AreEqual(reinterpret_cast<const char*>(&expected[0]), reinterpret_cast<const char*>(&container.GetByteString(key)[0]));
		}

		TEST_METHOD(SetByteString_WhenContainerHasNotValueWithGivenKey_InsertsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			byte_string expected = (const uint8_t*)"Hello world!";

			// Act
			container.SetByteString(key, expected);

			// Assert
			Assert::AreEqual(reinterpret_cast<const char*>(&expected[0]), reinterpret_cast<const char*>(&container.GetByteString(key)[0]));
		}

		TEST_METHOD(SetByteStringByRValue_WhenContainerHasValueWithGivenKey_UpdatesValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			byte_string expected = (const uint8_t*)"Hello world!";
			container.SetString(key, oldValue);

			// Act
			byte_string expectedCopy = expected;
			container.SetByteString(key, std::move(expectedCopy));

			// Assert
			Assert::AreEqual(reinterpret_cast<const char*>(&expected[0]), reinterpret_cast<const char*>(&container.GetByteString(key)[0]));
		}

		TEST_METHOD(SetByteStringByRValue_WhenContainerHasNotValueWithGivenKey_InsertsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			byte_string expected = (const uint8_t*)"Hello world!";

			// Act
			byte_string expectedCopy = expected;
			container.SetByteString(key, std::move(expectedCopy));

			// Assert
			Assert::AreEqual(reinterpret_cast<const char*>(&expected[0]), reinterpret_cast<const char*>(&container.GetByteString(key)[0]));
		}

		TEST_METHOD(SetFloat_WhenContainerHasValueWithGivenKey_UpdatesValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			float expected = 3.57F;
			container.SetString(key, oldValue);

			// Act
			container.SetFloat(key, expected);

			// Assert
			Assert::AreEqual(expected, container.GetFloat(key));
		}

		TEST_METHOD(SetFloat_WhenContainerHasNotValueWithGivenKey_InsertsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			float expected = 3.57F;

			// Act
			container.SetFloat(key, expected);

			// Assert
			Assert::AreEqual(expected, container.GetFloat(key));
		}

		TEST_METHOD(SetDouble_WhenContainerHasValueWithGivenKey_UpdatesValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			double expected = 3.57;
			container.SetString(key, oldValue);

			// Act
			container.SetDouble(key, expected);

			// Assert
			Assert::AreEqual(expected, container.GetDouble(key));
		}

		TEST_METHOD(SetDouble_WhenContainerHasNotValueWithGivenKey_InsertsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			double expected = 3.57;

			// Act
			container.SetDouble(key, expected);

			// Assert
			Assert::AreEqual(expected, container.GetDouble(key));
		}

		TEST_METHOD(GetInt32_WhenContainerHasValueOfGivenTypeWithGivenKey_ReturnsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			int32_t expected = 13;
			container.SetInt32(key, expected);

			// Act / Assert
			Assert::AreEqual(expected, container.GetInt32(key));
		}

		TEST_METHOD(GetInt32_WhenContainerHasNotValueWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetInt32(key); });
		}

		TEST_METHOD(GetInt32_WhenContainerHasValueOfIncorrectTypeWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			container.SetString(key, oldValue);

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetInt32(key); });
		}

		TEST_METHOD(GetInt64_WhenContainerHasValueOfGivenTypeWithGivenKey_ReturnsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			int64_t expected = 13;
			container.SetInt64(key, expected);

			// Act / Assert
			Assert::AreEqual(expected, container.GetInt64(key));
		}

		TEST_METHOD(GetInt64_WhenContainerHasNotValueWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetInt64(key); });
		}

		TEST_METHOD(GetInt64_WhenContainerHasValueOfIncorrectTypeWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			container.SetString(key, oldValue);

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetInt64(key); });
		}

		TEST_METHOD(GetBoolean_WhenContainerHasValueOfGivenTypeWithGivenKey_ReturnsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			bool expected = true;
			container.SetBoolean(key, expected);

			// Act / Assert
			Assert::AreEqual(expected, container.GetBoolean(key));
		}

		TEST_METHOD(GetBoolean_WhenContainerHasNotValueWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetBoolean(key); });
		}

		TEST_METHOD(GetBoolean_WhenContainerHasValueOfIncorrectTypeWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			container.SetString(key, oldValue);

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetBoolean(key); });
		}

		TEST_METHOD(GetString_WhenContainerHasValueOfGivenTypeWithGivenKey_ReturnsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string expected = "Hello world";
			container.SetString(key, expected);

			// Act / Assert
			Assert::AreEqual(expected, container.GetString(key));
		}

		TEST_METHOD(GetString_WhenContainerHasNotValueWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetString(key); });
		}

		TEST_METHOD(GetString_WhenContainerHasValueOfIncorrectTypeWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			bool oldValue = false;
			container.SetBoolean(key, oldValue);

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetString(key); });
		}

		TEST_METHOD(GetByteString_WhenContainerHasValueOfGivenTypeWithGivenKey_ReturnsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			byte_string expected = (const uint8_t*)"Hello world";
			container.SetByteString(key, expected);

			// Act / Assert
			Assert::AreEqual(reinterpret_cast<const char*>(&expected[0]), reinterpret_cast<const char*>(&container.GetByteString(key)[0]));
		}

		TEST_METHOD(GetByteString_WhenContainerHasNotValueWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetByteString(key); });
		}

		TEST_METHOD(GetByteString_WhenContainerHasValueOfIncorrectTypeWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			bool oldValue = false;
			container.SetBoolean(key, oldValue);

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetByteString(key); });
		}

		TEST_METHOD(GetFloat_WhenContainerHasValueOfGivenTypeWithGivenKey_ReturnsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			float expected = 13.5F;
			container.SetFloat(key, expected);

			// Act / Assert
			Assert::AreEqual(expected, container.GetFloat(key));
		}

		TEST_METHOD(GetFloat_WhenContainerHasNotValueWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetFloat(key); });
		}

		TEST_METHOD(GetFloat_WhenContainerHasValueOfIncorrectTypeWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			container.SetString(key, oldValue);

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetFloat(key); });
		}

		TEST_METHOD(GetDouble_WhenContainerHasValueOfGivenTypeWithGivenKey_ReturnsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			double expected = 13.5;
			container.SetDouble(key, expected);

			// Act / Assert
			Assert::AreEqual(expected, container.GetDouble(key));
		}

		TEST_METHOD(GetDouble_WhenContainerHasNotValueWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetDouble(key); });
		}

		TEST_METHOD(GetDouble_WhenContainerHasValueOfIncorrectTypeWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			container.SetString(key, oldValue);

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetDouble(key); });
		}

		TEST_METHOD(SetContainer_WhenContainerHasValueWithGivenKey_UpdatesValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			container.SetString(key, oldValue);

			// Act
			const auto& value = container.SetContainer(key);

			// Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetString(key); });
			Assert::IsTrue(container[key].IsContainer());
			Assert::IsTrue(value.Empty());
		}

		TEST_METHOD(SetContainer_WhenContainerHasNotValueWithGivenKey_InsertsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			// Act
			const auto& value = container.SetContainer(key);

			// Assert
			Assert::IsTrue(container.HasValue(key));
			Assert::IsTrue(container[key].IsContainer());
			Assert::IsTrue(value.Empty());
		}

		TEST_METHOD(SetContainerByLValue_WhenContainerHasValueWithGivenKey_UpdatesValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			std::string testKey = "test";
			std::string testValue = "Hello world";
			DataContainer value = DataContainer();
			value.SetString(testKey, testValue);

			std::string oldValue = "Some old value";
			container.SetString(key, oldValue);


			// Act
			container.SetContainer(key, value);

			// Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetString(key); });
			Assert::IsTrue(container[key].IsContainer());
			Assert::AreEqual(testValue, container.GetContainer(key).GetString(testKey));
		}

		TEST_METHOD(SetContainerByLValue_WhenContainerHasNotValueWithGivenKey_InsertsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			std::string testKey = "test";
			std::string testValue = "Hello world";
			DataContainer value = DataContainer();
			value.SetString(testKey, testValue);

			// Act
			container.SetContainer(key, value);

			// Assert
			Assert::IsTrue(container.HasValue(key));
			Assert::IsTrue(container[key].IsContainer());
			Assert::AreEqual(testValue, container.GetContainer(key).GetString(testKey));
		}

		TEST_METHOD(SetContainerByRValue_WhenContainerHasValueWithGivenKey_UpdatesValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			std::string testKey = "test";
			std::string testValue = "Hello world";
			DataContainer value = DataContainer();
			value.SetString(testKey, testValue);

			std::string oldValue = "Some old value";
			container.SetString(key, oldValue);


			// Act
			container.SetContainer(key, std::move(value));

			// Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetString(key); });
			Assert::IsTrue(container[key].IsContainer());
			Assert::AreEqual(testValue, container.GetContainer(key).GetString(testKey));
		}

		TEST_METHOD(SetContainerByRValue_WhenContainerHasNotValueWithGivenKey_InsertsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			std::string testKey = "test";
			std::string testValue = "Hello world";
			DataContainer value = DataContainer();
			value.SetString(testKey, testValue);

			// Act
			container.SetContainer(key, std::move(value));

			// Assert
			Assert::IsTrue(container.HasValue(key));
			Assert::IsTrue(container[key].IsContainer());
			Assert::AreEqual(testValue, container.GetContainer(key).GetString(testKey));
		}

		TEST_METHOD(GetContainer_WhenContainerHasContainerWithGivenKey_ReturnsContainer)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			std::string testKey = "test";
			std::string testValue = "Hello world";
			DataContainer oldValue = DataContainer();
			oldValue.SetString(testKey, testValue);

			container.SetContainer(key, oldValue);

			// Act
			const auto& value = container.GetContainer(key);

			// Assert
			Assert::AreEqual(testValue, value.GetString(testKey));
		}

		TEST_METHOD(GetContainer_WhenContainerHasNotValueWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetContainer(key); });
		}

		TEST_METHOD(GetContainer_WhenContainerHasValueOfIncorrectTypeWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			container.SetString(key, oldValue);

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetContainer(key); });
		}

		TEST_METHOD(GetContainerConst_WhenContainerHasContainerWithGivenKey_ReturnsContainer)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			std::string testKey = "test";
			std::string testValue = "Hello world";
			DataContainer oldValue = DataContainer();
			oldValue.SetString(testKey, testValue);

			container.SetContainer(key, oldValue);

			const DataContainer& constContainer = container;

			// Act
			auto& value = constContainer.GetContainer(key);

			// Assert
			Assert::AreEqual(testValue, value.GetString(testKey));
		}

		TEST_METHOD(GetContainerConst_WhenContainerHasNotValueWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			const DataContainer& constContainer = container;

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { constContainer.GetContainer(key); });
		}

		TEST_METHOD(GetContainerConst_WhenContainerHasValueOfIncorrectTypeWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			container.SetString(key, oldValue);

			const DataContainer& constContainer = container;

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { constContainer.GetContainer(key); });
		}

		TEST_METHOD(SetArray_WhenContainerHasValueWithGivenKey_UpdatesValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			container.SetString(key, oldValue);

			// Act
			const auto& value = container.SetArray(key);

			// Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetString(key); });
			Assert::IsTrue(container[key].IsArray());
			Assert::IsTrue(value.empty());
		}

		TEST_METHOD(SetArray_WhenContainerHasNotValueWithGivenKey_InsertsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			// Act
			const auto& value = container.SetArray(key);

			// Assert
			Assert::IsTrue(container.HasValue(key));
			Assert::IsTrue(container[key].IsArray());
			Assert::IsTrue(value.empty());
		}

		TEST_METHOD(SetArrayByLValue_WhenContainerHasValueWithGivenKey_UpdatesValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			std::vector<Value> value;
			std::string expected1 = "Hello";
			std::string expected2 = "World";
			value.push_back(Value(expected1));
			value.push_back(Value(expected2));

			std::string oldValue = "Some old value";
			container.SetString(key, oldValue);


			// Act
			container.SetArray(key, value);

			// Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetString(key); });
			Assert::IsTrue(container[key].IsArray());
			Assert::AreEqual(expected1, container.GetArray(key)[0].AsString());
			Assert::AreEqual(expected2, container.GetArray(key)[1].AsString());
		}

		TEST_METHOD(SetArrayByLValue_WhenContainerHasNotValueWithGivenKey_InsertsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			std::vector<Value> value;
			std::string expected1 = "Hello";
			std::string expected2 = "World";
			value.push_back(Value(expected1));
			value.push_back(Value(expected2));

			// Act
			container.SetArray(key, value);

			// Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetString(key); });
			Assert::IsTrue(container[key].IsArray());
			Assert::AreEqual(expected1, container.GetArray(key)[0].AsString());
			Assert::AreEqual(expected2, container.GetArray(key)[1].AsString());
		}

		TEST_METHOD(SetArrayByRValue_WhenContainerHasValueWithGivenKey_UpdatesValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			std::vector<Value> value;
			std::string expected1 = "Hello";
			std::string expected2 = "World";
			value.push_back(Value(expected1));
			value.push_back(Value(expected2));

			std::string oldValue = "Some old value";
			container.SetString(key, oldValue);


			// Act
			container.SetArray(key, std::move(value));

			// Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetString(key); });
			Assert::IsTrue(container[key].IsArray());
			Assert::AreEqual(expected1, container.GetArray(key)[0].AsString());
			Assert::AreEqual(expected2, container.GetArray(key)[1].AsString());
		}

		TEST_METHOD(SetArrayByRValue_WhenContainerHasNotValueWithGivenKey_InsertsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			std::vector<Value> value;
			std::string expected1 = "Hello";
			std::string expected2 = "World";
			value.push_back(Value(expected1));
			value.push_back(Value(expected2));

			// Act
			container.SetArray(key, std::move(value));

			// Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetString(key); });
			Assert::IsTrue(container[key].IsArray());
			Assert::AreEqual(expected1, container.GetArray(key)[0].AsString());
			Assert::AreEqual(expected2, container.GetArray(key)[1].AsString());
		}

		TEST_METHOD(GetArray_WhenContainerHasArrayWithGivenKey_ReturnsContainer)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			std::vector<Value> expectedValue;
			std::string expected1 = "Hello";
			std::string expected2 = "World";
			expectedValue.push_back(Value(expected1));
			expectedValue.push_back(Value(expected2));

			container.SetArray(key, expectedValue);

			// Act
			const auto& value = container.GetArray(key);

			// Assert
			Assert::IsTrue(expectedValue == value);
		}

		TEST_METHOD(GetArray_WhenContainerHasNotVaueWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetArray(key); });
		}

		TEST_METHOD(GetArray_WhenContainerHasValueOfIncorrectTypeWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			container.SetString(key, oldValue);

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { container.GetArray(key); });
		}

		TEST_METHOD(GetArrayConst_WhenContainerHasArrayWithGivenKey_ReturnsContainer)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			std::vector<Value> expectedValue;
			std::string expected1 = "Hello";
			std::string expected2 = "World";
			expectedValue.push_back(Value(expected1));
			expectedValue.push_back(Value(expected2));

			container.SetArray(key, expectedValue);
			const DataContainer& constContainer = container;

			// Act
			auto& value = constContainer.GetArray(key);

			// Assert
			Assert::IsTrue(expectedValue == value);
		}

		TEST_METHOD(GetArrayConst_WhenContainerHasNotVaueWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			const DataContainer& constContainer = container;

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { constContainer.GetArray(key); });
		}

		TEST_METHOD(GetArrayConst_WhenContainerHasValueOfIncorrectTypeWithGivenKey_AssertFailed)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string oldValue = "Some old value";
			container.SetString(key, oldValue);
			const DataContainer& constContainer = container;

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { constContainer.GetArray(key); });
		}
	};
}