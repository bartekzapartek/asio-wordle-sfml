#include "Game.h"
#include <sstream>
Game::Game() :  mDrawnByServerWord("unknown"), mCurrentUserWord(""), mTryCount(0)
{
	mLetters.resize(25, Letter());
	gameCurrentState = game_state::user_is_playing;
}

Game::~Game()
{

}

void Game::Update()
{

}

void Game::UpdateTypedWord(char letter)
{

	if (mCurrentUserWord.size() <= 4)
	{
		mCurrentUserWord.push_back(letter);

		std::stringstream sLetter;
		sLetter << letter;
		mLetters[mCurrentUserWord.size() - 1 + mTryCount * 5].SetTextDisplay(sLetter.str());
	}
}

void Game::SendGuessedWordToValidationCheck(network::ClientInterace& client)
{
	if (mCurrentUserWord.size() == 5)
		client.Send(network::Message(network::Message::message_header_info::client_send_word_to_validate, mCurrentUserWord));
}

void Game::InformServerAboutDisconnection(network::ClientInterace& client)
{
	client.Send(network::Message(network::Message::message_header_info::client_disconnect, "discon"));
}

std::string Game::GetWordDrawnByServer()
{
	return mDrawnByServerWord;
}

void Game::SetNextRound(std::string correctLettersPosition)
{
	EstablishCorrectLettersColors(correctLettersPosition);

	mCurrentUserWord = "";

	mTryCount++;
}

void Game::SetWordNotInDictionaryGameState()
{
	gameCurrentState = game_state::user_word_not_in_dictionary;
}

void Game::SetWinGameState()
{
	gameCurrentState = game_state::user_won;
}

void Game::SetUserPlayingGameState()
{
	gameCurrentState = game_state::user_is_playing;
}

void Game::SetDefeatedGameState(std::string wordDrawnByServer)
{
	gameCurrentState = game_state::user_lost;
	mDrawnByServerWord = wordDrawnByServer;
}

void Game::ResetGame()
{
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			mLetters[x + y * 5].SetTextDisplay("");
			mLetters[x + y * 5].setFillColor(sf::Color::Black);
		}
	}

	mCurrentUserWord = "";
	mTryCount = 0;
	gameCurrentState = Game::game_state::user_is_playing;
}

void Game::EstablishCorrectLettersColors(const std::string& correctLettersPosition)
{
	std::cout << "Letter Pos: " << correctLettersPosition << std::endl;
	for (int i = 0; i < correctLettersPosition.size(); i++)
	{
		if (correctLettersPosition[i] == '#') mLetters[i + mTryCount * 5].SetGreenColor();
		else if (correctLettersPosition[i] == '!') mLetters[i + mTryCount * 5].SetYellowColor();
	}
}

void Game::DeleteLeastTypedCharacter()
{
	if (mCurrentUserWord.size() == 0) return;
	mLetters[mCurrentUserWord.size() - 1 + mTryCount * 5].SetTextDisplay("");
	mCurrentUserWord.pop_back();
}



Game::game_state Game::GetGameState()
{
	return gameCurrentState;
}

std::vector<Letter>& Game::GetLetters()
{
	return mLetters;
}




