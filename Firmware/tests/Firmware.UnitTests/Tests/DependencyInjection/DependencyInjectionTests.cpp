#include "CppUnitTest.h"
#include "../../Mocks/Logger/DebugLogger.h"
#include "DependencyInjection/ContainerBuilder/ContainerBuilder.h"

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

	TEST_CLASS(DependencyInjectionUnitTests)
	{
	public:
		TEST_METHOD(AddSingleton_WhenBindingServiceByInterfaceWithoutArguments_ContainerReturnsSameServiceForEachCall)
		{
			// Arrange
			ContainerBuilder builder;
			int newNumber = 1;

			// Act
			builder.AddSingleton<TestInheritedClass, TestClassBase>();
			auto container = builder.Build();

			// Assert
			auto firstInstance = container->Resolve<TestClassBase>();
			firstInstance->number_ = newNumber;

			auto secondInstance = container->Resolve<TestClassBase>();

			Assert::AreEqual(newNumber, secondInstance->number_);
		}

		TEST_METHOD(AddSingleton_WhenBindingServiceByInterfaceWithPointerToService_ContainerReturnsSameServiceForEachCall)
		{
			// Arrange
			ContainerBuilder builder;
			int newNumber = 1;
			TestInheritedClass* service = new TestInheritedClass();

			// Act
			builder.AddSingleton<TestInheritedClass, TestClassBase>(service);
			auto container = builder.Build();

			// Assert
			auto firstInstance = container->Resolve<TestClassBase>();
			firstInstance->number_ = newNumber;

			auto secondInstance = container->Resolve<TestClassBase>();

			Assert::AreEqual(newNumber, secondInstance->number_);
		}

		TEST_METHOD(AddSingleton_WhenBindingServiceByInterfaceWithServiceCreator_ContainerReturnsSameServiceForEachCall)
		{
			// Arrange
			ContainerBuilder builder;
			int newNumber = 1;

			// Act
			builder.AddSingleton<TestInheritedClass, TestClassBase>([]() { return new TestInheritedClass(); });
			auto container = builder.Build();

			// Assert
			auto firstInstance = container->Resolve<TestClassBase>();
			firstInstance->number_ = newNumber;

			auto secondInstance = container->Resolve<TestClassBase>();

			Assert::AreEqual(newNumber, secondInstance->number_);
		}

		TEST_METHOD(AddSingleton_WhenBindingAsSelfWithoutArguments_ContainerReturnsSameServiceForEachCall)
		{
			// Arrange
			ContainerBuilder builder;
			int newNumber = 1;

			// Act
			builder.AddSingleton<TestClassBase>();
			auto container = builder.Build();

			// Assert
			auto firstInstance = container->Resolve<TestClassBase>();
			firstInstance->number_ = newNumber;

			auto secondInstance = container->Resolve<TestClassBase>();

			Assert::AreEqual(newNumber, secondInstance->number_);
		}

		TEST_METHOD(AddSingleton_WhenBindingAsSelfWithPointerToService_ContainerReturnsSameServiceForEachCall)
		{
			// Arrange
			ContainerBuilder builder;
			int newNumber = 1;
			TestClassBase* service = new TestClassBase();

			// Act
			builder.AddSingleton<TestClassBase>(service);
			auto container = builder.Build();

			// Assert
			auto firstInstance = container->Resolve<TestClassBase>();
			firstInstance->number_ = newNumber;

			auto secondInstance = container->Resolve<TestClassBase>();

			Assert::AreEqual(newNumber, secondInstance->number_);
		}

		TEST_METHOD(AddSingleton_WhenBindingAsSelfWithServiceCreator_ContainerReturnsSameServiceForEachCall)
		{
			// Arrange
			ContainerBuilder builder;
			int newNumber = 1;

			// Act
			builder.AddSingleton<TestClassBase>([]() { return new TestClassBase(); });
			auto container = builder.Build();

			// Assert
			auto firstInstance = container->Resolve<TestClassBase>();
			firstInstance->number_ = newNumber;

			auto secondInstance = container->Resolve<TestClassBase>();

			Assert::AreEqual(newNumber, secondInstance->number_);
		}

		TEST_METHOD(AddTransient_WhenBindingServiceByInterfaceWithoutArguments_ContainerReturnsNewServiceForEachCall)
		{
			// Arrange
			ContainerBuilder builder;
			int newNumber = 1;

			// Act
			builder.AddTransient<TestInheritedClass, TestClassBase>();
			auto container = builder.Build();

			// Assert
			auto firstInstance = container->Resolve<TestClassBase>();
			firstInstance->number_ = newNumber;

			auto secondInstance = container->Resolve<TestClassBase>();

			Assert::AreNotEqual(newNumber, secondInstance->number_);
		}

		TEST_METHOD(AddTransient_WhenBindingServiceByInterfaceWithServiceCreator_ContainerReturnsNewServiceForEachCall)
		{
			// Arrange
			ContainerBuilder builder;
			int newNumber = 1;

			// Act
			builder.AddTransient<TestInheritedClass, TestClassBase>([]() { return new TestInheritedClass(); });
			auto container = builder.Build();

			// Assert
			auto firstInstance = container->Resolve<TestClassBase>();
			firstInstance->number_ = newNumber;

			auto secondInstance = container->Resolve<TestClassBase>();

			Assert::AreNotEqual(newNumber, secondInstance->number_);
		}

		TEST_METHOD(AddTransient_WhenBindingAsSelfWithoutArguments_ContainerReturnsNewServiceForEachCall)
		{
			// Arrange
			ContainerBuilder builder;
			int newNumber = 1;

			// Act
			builder.AddTransient<TestClassBase>();
			auto container = builder.Build();

			// Assert
			auto firstInstance = container->Resolve<TestClassBase>();
			firstInstance->number_ = newNumber;

			auto secondInstance = container->Resolve<TestClassBase>();

			Assert::AreNotEqual(newNumber, secondInstance->number_);
		}

		TEST_METHOD(AddTransient_WhenBindingAsSelfWithServiceCreator_ContainerReturnsNewServiceForEachCall)
		{
			// Arrange
			ContainerBuilder builder;
			int newNumber = 1;

			// Act
			builder.AddTransient<TestClassBase>([]() { return new TestClassBase(); });
			auto container = builder.Build();

			// Assert
			auto firstInstance = container->Resolve<TestClassBase>();
			firstInstance->number_ = newNumber;

			auto secondInstance = container->Resolve<TestClassBase>();

			Assert::AreNotEqual(newNumber, secondInstance->number_);
		}

		TEST_METHOD(AddSingleton_WhenSeveralObjectsRegistered_ContainerReturnsCorrespondingObjects)
		{
			// Arrange
			ContainerBuilder builder;
			float expectedFloat = -2;
			int expectedInt = 338236;
			int expectedNumberInClass = 17;

			// Act
			builder.AddSingleton<float>([=]() { return new float(expectedFloat); });
			builder.AddSingleton<int>([=]() { return new int(expectedInt); });
			builder.AddSingleton<TestClassBase>([=]()
				{
					auto tmp = new TestClassBase();
					tmp->number_ = expectedNumberInClass;
					return tmp;
				});

			auto container = builder.Build();

			// Assert
			auto actualFloat = *container->Resolve<float>();
			auto actualInt = *container->Resolve<int>();
			auto actualNumberInClass = container->Resolve<TestClassBase>()->number_;

			Assert::AreEqual(expectedFloat, actualFloat);
			Assert::AreEqual(expectedInt, actualInt);
			Assert::AreEqual(expectedNumberInClass, actualNumberInClass);
		}
	};
}