#include "Message.h"

network::Message::Message(message_header_info messageHeaderInfo, std::string word):
	mMessageHeader(messageHeaderInfo), mMessageWord(word)
{
	
}

network::Message::Message(const Message& message)
{
	this->SetMessageHeader(message.mMessageHeader);
	this->SetMessageWord(message.mMessageWord);
}


std::string network::Message::GetMessageWord() const
{
	return mMessageWord;
}

network::Message::message_header_info network::Message::GetMessageHeaderInfo() const
{
	return mMessageHeader;
}

network::Message::message_header_info* network::Message::GetHeaderInfoBuffer()
{
	return &mMessageHeader;
}

char* network::Message::GetMessageWordBuffer()
{
	return mMessageWord.data();
}

void network::Message::SetMessageHeader(message_header_info messageHeaderInfo)
{
	mMessageHeader = messageHeaderInfo;
}

void network::Message::SetMessageWord(const std::string& word)
{
	mMessageWord = word;
}

network::Message& network::Message::operator+(const Message& message)
{
	this->SetMessageWord(message.GetMessageWord() + this->GetMessageWord());
	return *this;
}

std::string& network::operator>>(const network::Message& message, std::string& word)
{
	word = message.GetMessageWord();
	return word;
}

std::ostream& network::operator<<(std::ostream& stream, const Message& message)
{
	stream << message.GetMessageWord();
	return stream;
}

bool network::Message::operator==(std::string word)
{
	return (word == this->GetMessageWord());
}

network::Message& network::operator<<(Message& message, const std::string& word)
{
	message.SetMessageWord(word);
	return message;
}

