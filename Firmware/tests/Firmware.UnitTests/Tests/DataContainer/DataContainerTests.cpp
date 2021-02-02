#include "CppUnitTest.h"
#include "DataContainer/Value/Value.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace junjinjen_matrix::firmware::data_container;

namespace JunjinjenMatrixUnitTests
{
	TEST_CLASS(DataContainerUnitTests)
	{
	public:
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
			std::string newData = "New test value";
			container.SetValue(key, Value(oldData));

			// Act
			container.SetValue(key, Value(newData));

			// Assert
			Assert::IsTrue(container.HasValue(key));
			Assert::AreEqual(newData, container.GetString(key));
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

		TEST_METHOD(GetValue_WhenContainerHasNotValueWithGivenKey_ThrowsOutOfRange)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			// Act / Assert
			Assert::ExpectException<std::out_of_range>([&]() { container.GetValue(key); });
		}

		TEST_METHOD(GetValue_WhenContainerHasValueWithGivenKey_ReturnsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string expected = "Test value";
			container.SetValue(key, Value(expected));
			
			// Assert
			auto value = container.GetValue(key);

			// Act 
			Assert::AreEqual(expected, value.GetString());
		}

		TEST_METHOD(Indexator_WhenContainerHasValueWithGivenKey_ReturnsValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";
			std::string expected = "Test value";
			container.SetValue(key, Value(expected));

			// Assert
			auto value = container[key];

			// Act 
			Assert::AreEqual(expected, value.GetString());
		}

		TEST_METHOD(Indexator_WhenContainerHasNotValueWithGivenKey_ReturnsEmptyValue)
		{
			// Arrange
			DataContainer container;
			std::string key = "tmp";

			// Assert
			auto value = container[key];

			// Act 
			Assert::IsTrue(value.Empty());
			Assert::IsTrue(container.HasValue(key));
		}
	};
}