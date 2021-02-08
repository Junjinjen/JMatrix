#include "CppUnitTest.h"
#include "../../Mocks/Logger/DebugLogger.h"
#include "DependencyInjection/ContainerBuilder/ContainerBuilder.h"
#include "DependencyInjection/Container/Container.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace junjinjen_matrix::firmware::dependency_injection;

namespace DependencyInjectionTests
{
	class TestClassBase
	{
	public:
		int number_ = 0;
	};

	class TestInheritedClass : public TestClassBase
	{
	public:
		int secondNumber_ = 0;
	};

	TEST_CLASS(ContanierTests)
	{
		TEST_METHOD(Resolve_WhenContainerContainsRequestedInterfaceAsSelf_ReturnsInstance)
		{
			// Arrange
			ContainerBuilder builder;
			int expected = 15;
			auto base = new TestClassBase();
			base->number_ = expected;

			builder.AddSingleton<TestClassBase>(base);
			builder.Build();

			// Act
			auto ptr = Container::GetInstance()->Resolve<TestClassBase>();

			// Assert
			Assert::AreEqual(expected, ptr->number_);
		}

		TEST_METHOD(Resolve_WhenContainerContainsRequestedInterfaceAsService_ReturnsInstance)
		{
			// Arrange
			ContainerBuilder builder;
			int expected = 15;
			auto base = new TestInheritedClass();
			base->number_ = expected;

			builder.AddSingleton<TestInheritedClass, TestClassBase>(base);
			builder.Build();

			// Act
			auto ptr = Container::GetInstance()->Resolve<TestClassBase>();

			// Assert
			Assert::AreEqual(expected, ptr->number_);
		}

		TEST_METHOD(Resolve_WhenContainerDoesNotContainsRequestedInterface_AssertFailed)
		{
			// Arrange
			ContainerBuilder builder;
			builder.Build();

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([]() { Container::GetInstance()->Resolve<TestClassBase>(); });
		}
	};
}
