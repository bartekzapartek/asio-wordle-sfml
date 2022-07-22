#pragma once

#include "Include.h"
#include <fstream>
#include <algorithm>





class WordleGameServer : public network::ServerInterface
{
private:
	std::unordered_map<std::shared_ptr<network::ServerConnectionHandler>, std::string> mDrawnWord;

	std::unordered_map<std::shared_ptr<network::ServerConnectionHandler>, int> mMapClientWithTryCount;
	std::vector<std::string> mDictionary;

public:

	WordleGameServer(unsigned int port);

protected:

	int IncreaseClientTryCount(std::shared_ptr<network::ServerConnectionHandler> serverWithClientHandler);
	void ResetClientTryCount(std::shared_ptr<network::ServerConnectionHandler> serverWithClientHandler);

	bool CheckIfClientGuessedWordIsInDictionary(const std::string& clientGuessedWord);
	void CheckIfClientGuessedWord(network::Message& message, std::shared_ptr<network::ServerConnectionHandler> serverWithClientHandler);

	void ShouldLetterBeGreen(std::string& clientGuessedWord, std::shared_ptr<network::ServerConnectionHandler> serverWithClientHandler);
	void ShouldLetterBeYellow(std::string& clientGuessedWord, std::shared_ptr<network::ServerConnectionHandler> serverWithClientHandler);

	void GetDictionaryFromFile();
	void SetWordToGuess(std::shared_ptr<network::ServerConnectionHandler> serverWithClientHandler);

protected:

	void ActionAfterConnectionWihClientWasEstablished(std::shared_ptr<network::ServerConnectionHandler> serverWithClientHandler) override;
	void ActionAfterClientDisconnect(std::shared_ptr<network::ServerConnectionHandler> serverWithClientHandler) override;
	void ActionAfterMessageFromClientArrives(network::Message& message, std::shared_ptr<network::ServerConnectionHandler> serverWithClientHandler) override;
};