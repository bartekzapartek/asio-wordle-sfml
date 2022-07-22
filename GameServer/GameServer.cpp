#include "Server.h"
#include "GameServer.h"


WordleGameServer::WordleGameServer(unsigned int port) : network::ServerInterface(port)
{
	GetDictionaryFromFile();
}

void WordleGameServer::CheckIfClientGuessedWord(network::Message& message, std::shared_ptr<network::ServerConnectionHandler> serverWithClientHandler)
{
	std::string wordGuessedByClient;
	message >> wordGuessedByClient;

	std::cout << "WordGuessedByClient: " << message << std::endl;

	if (!CheckIfClientGuessedWordIsInDictionary(wordGuessedByClient))
	{
		serverWithClientHandler->Send(network::Message(network::Message::message_header_info::server_word_not_in_dictionary, wordGuessedByClient));
		return;
	}


	ShouldLetterBeGreen(wordGuessedByClient, serverWithClientHandler);



	if (message == mDrawnWord[serverWithClientHandler])
	{
		serverWithClientHandler->Send(network::Message(network::Message::message_header_info::server_establish_you_as_winner, wordGuessedByClient));
		SetWordToGuess(serverWithClientHandler);
		ResetClientTryCount(serverWithClientHandler);
		return;
	}
	
	int clientTryCount = IncreaseClientTryCount(serverWithClientHandler);
	//std::cout << "ClientTryCount: " << clientTryCount << " \n";

	if (clientTryCount == 5)
	{
		serverWithClientHandler->Send(network::Message(network::Message::message_header_info::server_established_you_as_defeated, mDrawnWord[serverWithClientHandler]));
		ResetClientTryCount(serverWithClientHandler);
		SetWordToGuess(serverWithClientHandler);
		return;
	}

	ShouldLetterBeYellow(wordGuessedByClient, serverWithClientHandler);

	serverWithClientHandler->Send(network::Message(network::Message::message_header_info::server_guess_again, wordGuessedByClient));

}

void WordleGameServer::ShouldLetterBeGreen(std::string& clientGuessedWord, std::shared_ptr<network::ServerConnectionHandler> serverWithClientHandler)
{
	for (int i = 0; i < clientGuessedWord.size(); i++)
	{
		if (clientGuessedWord[i] == mDrawnWord[serverWithClientHandler][i]) clientGuessedWord[i] = '#';

	}
}

void WordleGameServer::ShouldLetterBeYellow(std::string& clientGuessedWord, std::shared_ptr<network::ServerConnectionHandler> serverWithClientHandler)
{
	std::string copyOfDrawnWord = mDrawnWord[serverWithClientHandler];
	for (int i = 0; i < clientGuessedWord.size(); i++)
	{
		//std::cout << "Word: " << clientGuessedWord << std::endl;

		std::size_t letterFoundPosition = copyOfDrawnWord.find(clientGuessedWord[i]);
		if (letterFoundPosition != std::string::npos && clientGuessedWord[letterFoundPosition] != '#' && clientGuessedWord[letterFoundPosition] != '!')
		{
			clientGuessedWord[i] = '!';
			copyOfDrawnWord[letterFoundPosition] = '-';
		}
	}
}

int WordleGameServer::IncreaseClientTryCount(std::shared_ptr<network::ServerConnectionHandler> serverWithClientHandler)
{
	if (mMapClientWithTryCount.find(serverWithClientHandler) != mMapClientWithTryCount.end()) mMapClientWithTryCount[serverWithClientHandler]++;
	else mMapClientWithTryCount[serverWithClientHandler] = 1;
	
	return mMapClientWithTryCount[serverWithClientHandler];
}

void WordleGameServer::ResetClientTryCount(std::shared_ptr<network::ServerConnectionHandler> serverWithClientHandler)
{
	if (mMapClientWithTryCount.find(serverWithClientHandler) != mMapClientWithTryCount.end()) mMapClientWithTryCount[serverWithClientHandler] = 0;
	else return;
}


bool WordleGameServer::CheckIfClientGuessedWordIsInDictionary(const std::string& clientGuessedWord)
{
	return (std::find(mDictionary.begin(), mDictionary.end(), clientGuessedWord) != mDictionary.end() ? true : false);
}

void WordleGameServer::GetDictionaryFromFile()
{
	std::ifstream file("Dictionary.txt");
	if (!file.good())
	{
		std::cout << "ERROR::GAME_SERVER::GET_DICTIONARY_FROM_FILE():: file read error.\n";
		return;
	}

	mDictionary.reserve(50);
	std::string word;


	while (file.eof() == false)
	{
		std::getline(file, word);
		std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return std::toupper(c); });
		mDictionary.push_back(word);
	}

	file.close();
}

void WordleGameServer::SetWordToGuess(std::shared_ptr<network::ServerConnectionHandler> serverWithClientHandler)
{
	std::srand(time(NULL));
	if (mDictionary.size() == 0) mDrawnWord[serverWithClientHandler] = "janek";
	else mDrawnWord[serverWithClientHandler] = mDictionary[std::rand() % mDictionary.size()];
}

void WordleGameServer::ActionAfterConnectionWihClientWasEstablished(std::shared_ptr<network::ServerConnectionHandler> serverWithClientHandler)
{
	SetWordToGuess(serverWithClientHandler);
}

void WordleGameServer::ActionAfterClientDisconnect(std::shared_ptr<network::ServerConnectionHandler> serverWithClientHandler)
{

}

void WordleGameServer::ActionAfterMessageFromClientArrives(network::Message& message, std::shared_ptr<network::ServerConnectionHandler> serverWithClientHandler)
{
	switch (message.GetMessageHeaderInfo())
	{
	case network::Message::message_header_info::client_send_word_to_validate: CheckIfClientGuessedWord(message, serverWithClientHandler);  break;
	case network::Message::message_header_info::client_disconnect: ActionAfterClientDisconnect(serverWithClientHandler);  break;
	}
}


