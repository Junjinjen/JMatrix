#include "CppUnitTest.h"
#include "DependencyInjection/ContainerBuilder/ContainerBuilder.h"
#include "Messaging/Serialization/ContainerSerializer.h"
#include "Messaging/DataContainer/DataContainer.h"
#include "Services/TaskService/NetworkPipeline/PipeManagement/Pipe/Pipe.h"
#include "../../../Mocks/Logger/DebugLogger.h"
#include "../../../Mocks/Network/Client/MockClient.h"
#include <tuple>

#undef SendMessage

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace junjinjen_matrix::firmware::services::task_service::network_pipeline::pipe_management;
using namespace junjinjen_matrix::firmware::messaging;
using namespace junjinjen_matrix::firmware::messaging::serialization;
using namespace junjinjen_matrix::firmware::dependency_injection;

namespace TaskServiceUnitTests
{
	class TestSerializer : public ContainerSerializer
	{
	public:
		static DataContainer GenerateMessage(const std::string& message)
		{
			DataContainer container;
			container.SetString("message", message);
			return container;
		}

		virtual bool Serialize(const DataContainer& container, byte_string& outputBuffer) override
		{
			outputBuffer = reinterpret_cast<const uint8_t*>(&container.GetString("message")[0]);
			return true;
		}

		virtual bool Deserialize(const byte_string& inputBuffer, DataContainer& container) override
		{
			container.SetString("message", reinterpret_cast<const char*>(&inputBuffer[0]));
			return true;
		}
	};

	TEST_CLASS(PipeUnitTests)
	{
	public:
		TEST_CLASS_INITIALIZE(InitializeIocContainer)
		{
			ContainerBuilder builder;
			builder.AddSingleton<DebugLogger, junjinjen_matrix::firmware::logging::Logger>();
			builder.AddSingleton<TestSerializer, ContainerSerializer>();
			builder.Build();
		}

		TEST_METHOD(Connected_WhenClientConnected_ReturnsTrue)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			client->SetConnected(true);

			// Act / Assert
			Assert::IsTrue(pipe->Connected());
		}

		TEST_METHOD(Connected_WhenClientDisconnected_ReturnsFalse)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			client->SetConnected(false);

			// Act / Assert
			Assert::IsFalse(pipe->Connected());
		}

		TEST_METHOD(HasNewMessage_WhenClientHasMessage_ReturnsTrue)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			client->AddMessage("test");

			// Act / Assert
			Assert::IsTrue(pipe->HasNewMessage());
		}

		TEST_METHOD(HasNewMessage_WhenClientHasNotMessage_ReturnsFalse)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();

			// Act / Assert
			Assert::IsFalse(pipe->HasNewMessage());
		}

		TEST_METHOD(GetNewMessage_WhenMessagesWasNotLoaded_AssertFailed)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			auto expected = "Test";
			client->AddMessage(expected);

			// Act / Assert
			Assert::ExpectException<AssertFailedException>([&]() { pipe->GetNewMessage(); });
		}

		TEST_METHOD(GetNewMessage_WhenClientReturnsWholeMessage_ReturnsMessage)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			auto expected = "Test";
			client->AddMessage(expected);

			// Act / Assert
			Assert::IsTrue(pipe->HasNewMessage());
			Assert::IsTrue(TestSerializer::GenerateMessage(expected) == pipe->GetNewMessage());
		}

		TEST_METHOD(GetNewMessage_WhenClientReturnsMessageByBytes_ReturnsMessage)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			auto expected = "Test";

			auto rawMessage = client->GenerateMessage(expected);
			auto packagesCount = rawMessage.size();
			for (size_t i = 0; i < packagesCount; i++)
			{
				client->AddRawMessage(std::string(&rawMessage[i], 1));
			}

			// Act
			for (size_t i = 0; i < packagesCount - 2; i++)
			{
				Assert::IsFalse(pipe->HasNewMessage());
			}

			Assert::IsTrue(pipe->HasNewMessage());
			auto actual = pipe->GetNewMessage();

			// Assert
			Assert::IsTrue(TestSerializer::GenerateMessage(expected) == actual);
		}

		TEST_METHOD(GetNewMessage_WhenClientReturnsSeveralWholeMessages_ReturnsMessages)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			auto expected1 = "Test1";
			auto expected2 = "TestMessage2";
			auto expected3 = "hello world";

			client->AddMessage(expected1);
			client->AddMessage(expected2);
			client->AddMessage(expected3);

			// Act
			Assert::IsTrue(pipe->HasNewMessage());
			auto actual1 = pipe->GetNewMessage();

			Assert::IsTrue(pipe->HasNewMessage());
			auto actual2 = pipe->GetNewMessage();

			Assert::IsTrue(pipe->HasNewMessage());
			auto actual3 = pipe->GetNewMessage();

			// Assert
			Assert::IsTrue(TestSerializer::GenerateMessage(expected1) == actual1);
			Assert::IsTrue(TestSerializer::GenerateMessage(expected2) == actual2);
			Assert::IsTrue(TestSerializer::GenerateMessage(expected3) == actual3);
		}

		TEST_METHOD(GetNewMessage_WhenClientReturnsSeveralMessagesByBytes_ReturnsMessages)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			auto expected1 = "Test1";
			auto expected2 = "TestMessage2";
			auto expected3 = "hello world";

			auto rawMessage1 = client->GenerateMessage(expected1);
			auto packagesCount1 = rawMessage1.size();

			auto rawMessage2 = client->GenerateMessage(expected2);
			auto packagesCount2 = rawMessage2.size();

			auto rawMessage3 = client->GenerateMessage(expected3);
			auto packagesCount3 = rawMessage3.size();

			for (size_t i = 0; i < packagesCount1; i++)
			{
				client->AddRawMessage(std::string(&rawMessage1[i], 1));
			}

			for (size_t i = 0; i < packagesCount2; i++)
			{
				client->AddRawMessage(std::string(&rawMessage2[i], 1));
			}

			for (size_t i = 0; i < packagesCount3; i++)
			{
				client->AddRawMessage(std::string(&rawMessage3[i], 1));
			}

			// Act
			for (size_t i = 0; i < packagesCount1 - 2; i++)
			{
				Assert::IsFalse(pipe->HasNewMessage());
			}

			Assert::IsTrue(pipe->HasNewMessage());
			auto actual1 = pipe->GetNewMessage();

			for (size_t i = 0; i < packagesCount2 - 2; i++)
			{
				Assert::IsFalse(pipe->HasNewMessage());
			}

			Assert::IsTrue(pipe->HasNewMessage());
			auto actual2 = pipe->GetNewMessage();

			for (size_t i = 0; i < packagesCount3 - 2; i++)
			{
				Assert::IsFalse(pipe->HasNewMessage());
			}

			Assert::IsTrue(pipe->HasNewMessage());
			auto actual3 = pipe->GetNewMessage();

			// Assert
			Assert::IsTrue(TestSerializer::GenerateMessage(expected1) == actual1);
			Assert::IsTrue(TestSerializer::GenerateMessage(expected2) == actual2);
			Assert::IsTrue(TestSerializer::GenerateMessage(expected3) == actual3);
		}

		TEST_METHOD(GetNewMessage_WhenClientReturnsMessageByPartions_ReturnsMessage)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			auto expected = "Long test message!";
			bool oneMorePackage = false;
			size_t packagesCount = 4;
			client->AddMessage(expected, packagesCount, oneMorePackage);

			// Act
			for (size_t i = 0; i < packagesCount - (oneMorePackage ? 1 : 2); i++)
			{
				Assert::IsFalse(pipe->HasNewMessage());
			}

			Assert::IsTrue(pipe->HasNewMessage());
			auto actual = pipe->GetNewMessage();

			// Assert
			Assert::IsTrue(TestSerializer::GenerateMessage(expected) == actual);
		}

		TEST_METHOD(GetNewMessage_WhenClientReturnsMessagesByPartions_ReturnsMessages)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();

			auto expected1 = "Long test message!";
			bool oneMorePackage1 = false;
			size_t packagesCount1 = 4;

			auto expected2 = "Second long message.";
			bool oneMorePackage2 = false;
			size_t packagesCount2 = 6;

			auto expected3 = "Hello world??";
			bool oneMorePackage3 = false;
			size_t packagesCount3 = 40;

			client->AddMessage(expected1, packagesCount1, oneMorePackage1);
			client->AddMessage(expected2, packagesCount2, oneMorePackage2);
			client->AddMessage(expected3, packagesCount3, oneMorePackage3);

			// Act
			for (size_t i = 0; i < packagesCount1 - (oneMorePackage1 ? 1 : 2); i++)
			{
				Assert::IsFalse(pipe->HasNewMessage());
			}

			Assert::IsTrue(pipe->HasNewMessage());
			auto actual1 = pipe->GetNewMessage();

			for (size_t i = 0; i < packagesCount2 - (oneMorePackage2 ? 1 : 2); i++)
			{
				Assert::IsFalse(pipe->HasNewMessage());
			}

			Assert::IsTrue(pipe->HasNewMessage());
			auto actual2 = pipe->GetNewMessage();

			for (size_t i = 0; i < packagesCount3 - (oneMorePackage3 ? 1 : 2); i++)
			{
				Assert::IsFalse(pipe->HasNewMessage());
			}

			Assert::IsTrue(pipe->HasNewMessage());
			auto actual3 = pipe->GetNewMessage();

			// Assert
			Assert::IsTrue(TestSerializer::GenerateMessage(expected1) == actual1);
			Assert::IsTrue(TestSerializer::GenerateMessage(expected2) == actual2);
			Assert::IsTrue(TestSerializer::GenerateMessage(expected3) == actual3);
		}

		TEST_METHOD(SendMessage_WhenClientReceivesWholeMessage_ClientReturnsMessage)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			std::vector<uint8_t> expectedOutputVector;
			std::vector<uint8_t> assertionOutputVector;

			auto expected = "Test";
			AddToVector(expectedOutputVector, client->GenerateMessage(expected));

			// Act
			Assert::IsTrue(pipe->SendMessage(TestSerializer::GenerateMessage(expected)));

			// Assert
			for (auto& msg : client->GetOutput())
			{
				AddToVector(assertionOutputVector, msg);
			}

			Assert::IsTrue(expectedOutputVector == assertionOutputVector);
		}

		TEST_METHOD(SendMessage_WhenClientReceivesWholeMessages_ClientReturnsMessages)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			std::vector<uint8_t> expectedOutputVector;
			std::vector<uint8_t> assertionOutputVector;

			auto expected1 = "Test1";
			auto expected2 = "TestMessage2";
			auto expected3 = "hello world";

			AddToVector(expectedOutputVector, client->GenerateMessage(expected1));
			AddToVector(expectedOutputVector, client->GenerateMessage(expected2));
			AddToVector(expectedOutputVector, client->GenerateMessage(expected3));

			// Act
			Assert::IsTrue(pipe->SendMessage(TestSerializer::GenerateMessage(expected1)));
			Assert::IsTrue(pipe->SendMessage(TestSerializer::GenerateMessage(expected2)));
			Assert::IsTrue(pipe->SendMessage(TestSerializer::GenerateMessage(expected3)));

			// Assert
			for (auto& msg : client->GetOutput())
			{
				AddToVector(assertionOutputVector, msg);
			}

			Assert::IsTrue(expectedOutputVector == assertionOutputVector);
		}

		TEST_METHOD(SendMessage_WhenClientDoesNotReceiveWholeMessage_ReturnsFalse)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			client->SetMaxPackageSize(1);
			auto expected = "Message";

			// Act / Assert
			Assert::IsFalse(pipe->SendMessage(TestSerializer::GenerateMessage(expected)));
		}
	private:
		inline std::tuple<MockClient*, std::unique_ptr<Pipe>> ConfigureTestPipe()
		{
			auto client = new MockClient();
			auto pipe = std::make_unique<Pipe>(client);

			return std::make_tuple(client, std::move(pipe));
		}

		template<typename T>
		inline void AddToVector(std::vector<uint8_t>& vector, std::basic_string<T> string)
		{
			vector.insert(vector.end(), string.begin(), string.end());
		}
	};
}
