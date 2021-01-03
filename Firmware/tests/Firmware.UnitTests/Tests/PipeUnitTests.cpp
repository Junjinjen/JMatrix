#include "CppUnitTest.h"
#include "PipeManagement/Pipe/Pipe.h"
#include "../Mocks/Logger/DebugLogger.h"
#include "../Mocks/Network/Client/MockClient.h"
#include <tuple>

#undef SendMessage

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace junjinjen_matrix::firmware::pipe_management;

namespace UnitTestsJMatrix
{
	TEST_CLASS(PipeUnitTests)
	{
	public:
		TEST_METHOD(IsConnected_WhenClientConnected_ReturnsTrue)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			client->SetConnected(true);

			// Act / Assert
			Assert::IsTrue(pipe->IsConnected());
		}

		TEST_METHOD(IsConnected_WhenClientDisconnected_ReturnsFalse)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			client->SetConnected(false);

			// Act / Assert
			Assert::IsFalse (pipe->IsConnected());
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

		TEST_METHOD(GetNewMessage_WhenClientReturnsWholeMessage_ReturnsMessage)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			auto expected = "Test";
			client->AddMessage(expected);

			// Act
			auto actual = pipe->GetNewMessage();

			// Assert
			Assert::AreEqual(expected, reinterpret_cast<const char*>(&actual[0]));
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

			auto actual = pipe->GetNewMessage();
			// Assert
			Assert::AreEqual(expected, reinterpret_cast<const char*>(&actual[0]));
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
			auto actual1 = pipe->GetNewMessage();
			auto actual2 = pipe->GetNewMessage();
			auto actual3 = pipe->GetNewMessage();

			// Assert
			Assert::AreEqual(expected1, reinterpret_cast<const char*>(&actual1[0]));
			Assert::AreEqual(expected2, reinterpret_cast<const char*>(&actual2[0]));
			Assert::AreEqual(expected3, reinterpret_cast<const char*>(&actual3[0]));
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
			auto actual1 = pipe->GetNewMessage();

			for (size_t i = 0; i < packagesCount2 - 2; i++)
			{
				Assert::IsFalse(pipe->HasNewMessage());
			}
			auto actual2 = pipe->GetNewMessage();

			for (size_t i = 0; i < packagesCount3 - 2; i++)
			{
				Assert::IsFalse(pipe->HasNewMessage());
			}
			auto actual3 = pipe->GetNewMessage();

			// Assert
			Assert::AreEqual(expected1, reinterpret_cast<const char*>(&actual1[0]));
			Assert::AreEqual(expected2, reinterpret_cast<const char*>(&actual2[0]));
			Assert::AreEqual(expected3, reinterpret_cast<const char*>(&actual3[0]));
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

			auto actual = pipe->GetNewMessage();

			// Assert
			Assert::AreEqual(expected, reinterpret_cast<const char*>(&actual[0]));
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

			auto actual1 = pipe->GetNewMessage();

			for (size_t i = 0; i < packagesCount2 - (oneMorePackage2 ? 1 : 2); i++)
			{
				Assert::IsFalse(pipe->HasNewMessage());
			}

			auto actual2 = pipe->GetNewMessage();

			for (size_t i = 0; i < packagesCount3 - (oneMorePackage3 ? 1 : 2); i++)
			{
				Assert::IsFalse(pipe->HasNewMessage());
			}

			auto actual3 = pipe->GetNewMessage();

			// Assert
			Assert::AreEqual(expected1, reinterpret_cast<const char*>(&actual1[0]));
			Assert::AreEqual(expected2, reinterpret_cast<const char*>(&actual2[0]));
			Assert::AreEqual(expected3, reinterpret_cast<const char*>(&actual3[0]));
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
			Assert::IsTrue(pipe->SendMessage(expected));

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
			Assert::IsTrue(pipe->SendMessage(expected1));
			Assert::IsTrue(pipe->SendMessage(expected2));
			Assert::IsTrue(pipe->SendMessage(expected3));

			// Assert
			for (auto& msg : client->GetOutput())
			{
				AddToVector(assertionOutputVector, msg);
			}

			Assert::IsTrue(expectedOutputVector == assertionOutputVector);
		}

		TEST_METHOD(SendMessage_WhenClientReceivesMessageByBytes_ClientReturnsMessage)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			std::vector<uint8_t> expectedOutputVector;
			std::vector<uint8_t> assertionOutputVector;
			client->SetMaxPackageSize(1);

			auto expected = "Test1";

			AddToVector(expectedOutputVector, client->GenerateMessage(expected));

			// Act
			Assert::IsTrue(pipe->SendMessage(expected));

			// Assert
			for (auto& msg : client->GetOutput())
			{
				AddToVector(assertionOutputVector, msg);
			}

			Assert::IsTrue(expectedOutputVector == assertionOutputVector);
		}

		TEST_METHOD(SendMessage_WhenClientReceivesMessagesByBytes_ClientReturnsMessages)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			std::vector<uint8_t> expectedOutputVector;
			std::vector<uint8_t> assertionOutputVector;
			client->SetMaxPackageSize(1);

			auto expected1 = "Test1";
			auto expected2 = "TestMessage2";
			auto expected3 = "hello world";

			AddToVector(expectedOutputVector, client->GenerateMessage(expected1));
			AddToVector(expectedOutputVector, client->GenerateMessage(expected2));
			AddToVector(expectedOutputVector, client->GenerateMessage(expected3));

			// Act
			Assert::IsTrue(pipe->SendMessage(expected1));
			Assert::IsTrue(pipe->SendMessage(expected2));
			Assert::IsTrue(pipe->SendMessage(expected3));

			// Assert
			for (auto& msg : client->GetOutput())
			{
				AddToVector(assertionOutputVector, msg);
			}

			Assert::IsTrue(expectedOutputVector == assertionOutputVector);
		}

		TEST_METHOD(SendMessage_WhenClientReceivesMessageByParts_ClientReturnsMessage)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			std::vector<uint8_t> expectedOutputVector;
			std::vector<uint8_t> assertionOutputVector;
			client->SetMaxPackageSize(4);

			auto expected = "Test1";

			AddToVector(expectedOutputVector, client->GenerateMessage(expected));

			// Act
			Assert::IsTrue(pipe->SendMessage(expected));

			// Assert
			for (auto& msg : client->GetOutput())
			{
				AddToVector(assertionOutputVector, msg);
			}

			Assert::IsTrue(expectedOutputVector == assertionOutputVector);
		}

		TEST_METHOD(SendMessage_WhenClientReceivesMessagesByParts_ClientReturnsMessages)
		{
			// Arrange
			auto [client, pipe] = ConfigureTestPipe();
			std::vector<uint8_t> expectedOutputVector;
			std::vector<uint8_t> assertionOutputVector;
			
			auto expected1 = "Long test message!";
			auto expected2 = "Second long message.";
			auto expected3 = "Hello world??";

			AddToVector(expectedOutputVector, client->GenerateMessage(expected1));
			AddToVector(expectedOutputVector, client->GenerateMessage(expected2));
			AddToVector(expectedOutputVector, client->GenerateMessage(expected3));

			// Act
			client->SetMaxPackageSize(6);
			Assert::IsTrue(pipe->SendMessage(expected1));

			client->SetMaxPackageSize(1);
			Assert::IsTrue(pipe->SendMessage(expected2));

			client->SetMaxPackageSize(4);
			Assert::IsTrue(pipe->SendMessage(expected3));

			// Assert
			for (auto& msg : client->GetOutput())
			{
				AddToVector(assertionOutputVector, msg);
			}

			Assert::IsTrue(expectedOutputVector == assertionOutputVector);
		}
	private:
		inline std::tuple<MockClient*, std::unique_ptr<Pipe>> ConfigureTestPipe()
		{
			auto logger = std::make_shared<DebugLogger>();
			auto client = new MockClient();
			auto pipe = std::make_unique<Pipe>(logger, std::unique_ptr<MockClient>(client));

			return std::make_tuple(client, std::move(pipe));
		}

		template<typename T>
		inline void AddToVector(std::vector<uint8_t>& vector, std::basic_string<T>& string)
		{
			vector.insert(vector.end(), string.begin(), string.end());
		}
	};
}
