#include "CppUnitTest.h"
#include "../../Mocks/Logger/DebugLogger.h"
#include "DependencyInjection/ContainerBuilder/ContainerBuilder.h"

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

	TEST_CLASS(ContanierBuilderTests)
	{
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
			auto service = new TestInheritedClass();

			// Act
			builder.AddSingleton<TestInheritedClass, TestClassBase>(service);
			auto container = builder.Build();

			// Assert
			auto firstInstance = container->Resolve<TestClassBase>();
			firstInstance->number_ = newNumber;

			auto secondInstance = container->Resolve<TestClassBase>();

			Assert::AreEqual(newNumber, secondInstance->number_);
		}

		TEST_METHOD(AddSingleton_WhenBindingServiceByInterfaceWithSharedPointerToService_ContainerReturnsSameServiceForEachCall)
		{
			// Arrange
			ContainerBuilder builder;
			int newNumber = 1;
			auto service = std::make_shared<TestInheritedClass>();

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

		TEST_METHOD(AddSingleton_WhenBindingServiceByInterfaceWithServiceCreatorThatReturnsSharedPtr_ContainerReturnsSameServiceForEachCall)
		{
			// Arrange
			ContainerBuilder builder;
			int newNumber = 1;

			// Act
			builder.AddSingleton<TestInheritedClass, TestClassBase>([]() { return std::make_shared<TestInheritedClass>(); });
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
			auto service = new TestClassBase();

			// Act
			builder.AddSingleton<TestClassBase>(service);
			auto container = builder.Build();

			// Assert
			auto firstInstance = container->Resolve<TestClassBase>();
			firstInstance->number_ = newNumber;

			auto secondInstance = container->Resolve<TestClassBase>();

			Assert::AreEqual(newNumber, secondInstance->number_);
		}

		TEST_METHOD(AddSingleton_WhenBindingAsSelfWithSharedPointerToService_ContainerReturnsSameServiceForEachCall)
		{
			// Arrange
			ContainerBuilder builder;
			int newNumber = 1;
			auto service = std::make_shared<TestClassBase>();

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

		TEST_METHOD(AddSingleton_WhenBindingAsSelfWithServiceCreatorThatReturnsSharedPtr_ContainerReturnsSameServiceForEachCall)
		{
			// Arrange
			ContainerBuilder builder;
			int newNumber = 1;

			// Act
			builder.AddSingleton<TestClassBase>([]() { return std::make_shared<TestClassBase>(); });
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

		TEST_METHOD(AddTransient_WhenBindingServiceByInterfaceWithServiceCreatorThatReturnsSharedPtr_ContainerReturnsNewServiceForEachCall)
		{
			// Arrange
			ContainerBuilder builder;
			int newNumber = 1;

			// Act
			builder.AddTransient<TestInheritedClass, TestClassBase>([]() { return std::make_shared<TestInheritedClass>(); });
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

		TEST_METHOD(AddTransient_WhenBindingAsSelfWithServiceCreatorThatReturnsSharedPtr_ContainerReturnsNewServiceForEachCall)
		{
			// Arrange
			ContainerBuilder builder;
			int newNumber = 1;

			// Act
			builder.AddTransient<TestClassBase>([]() { return std::make_shared<TestClassBase>(); });
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
			builder.AddSingleton<float>([expectedFloat]() { return new float(expectedFloat); });
			builder.AddSingleton<int>([expectedInt]() { return new int(expectedInt); });
			builder.AddSingleton<TestClassBase>([expectedNumberInClass]()
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