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
	};
}