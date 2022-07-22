#pragma once
#include "CommonLibraries.h"
#include <unordered_map>
namespace network
{

	class Message
	{
	public:
		enum class message_header_info
		{
			client_try_to_connect,
			client_disconnect,

			client_send_word_to_validate,
			
			server_approve_connection,
			server_disapprove_connection,

			server_other_client_disconnected,
			server_word_not_in_dictionary,

			server_guess_again,

			server_establish_you_as_winner,
			server_established_you_as_defeated,

			none
		};

	private:

		message_header_info mMessageHeader;
		std::string mMessageWord;


	public:

		Message(message_header_info messageHeaderInfo, std::string word = "     ");
		Message(const Message& message);

		std::string GetMessageWord() const;
		message_header_info GetMessageHeaderInfo() const;
			
		message_header_info* GetHeaderInfoBuffer();
		char* GetMessageWordBuffer();


		void SetMessageHeader(message_header_info messageHeaderInfo);
		void SetMessageWord(const std::string& word);

		friend Message& operator<<(Message& message, const std::string& word);
		Message& operator+(const Message& message);
		friend std::string& operator>>(const Message& message, std::string& word);
		bool operator==(std::string word);

		friend std::ostream& operator<<(std::ostream& stream, const Message& message);
	};




	
}