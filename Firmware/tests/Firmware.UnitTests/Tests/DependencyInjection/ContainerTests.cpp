#include "CppUnitTest.h"
#include "../../Mocks/Logger/DebugLogger.h"
#include "DependencyInjection/ContainerBuilder/ContainerBuilder.h"
#include "DependencyInjection/Container/Container.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace junjinjen_matrix::firmware::dependency_injection;

namespace DependencyInjectionUnitTests
{
	class TestClassBase
	{
	public:
		TestClassBase() : number_(0) { }
		int number_;
	};

	class TestInheritedClass : public TestClassBase
	{
	public:
		TestInheritedClass() : secondNumber_(0) { }
		int secondNumber_;
	};

	TEST_CLASS(ContanierUnitTests)
	{
	public:
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
