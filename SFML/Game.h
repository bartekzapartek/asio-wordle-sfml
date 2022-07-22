#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Include.h"
#include "Letter.h"

class Game
{

public:

	enum class game_state
	{
		user_won,
		user_lost,
		user_is_playing,
		user_word_not_in_dictionary
	};



private:

	std::vector<Letter> mLetters;

	std::string mDrawnByServerWord;
	std::string mCurrentUserWord;
	unsigned int mTryCount;

	game_state gameCurrentState;

public:

	

	Game();
	~Game();



public:

	void Update();
	void UpdateTypedWord(char letter);


	void SetNextRound(std::string correctLettersPosition);
	void SetWordNotInDictionaryGameState();
	void SetWinGameState();
	void SetUserPlayingGameState();
	void SetDefeatedGameState(std::string wordDrawnByServer);

	void ResetGame();

	void EstablishCorrectLettersColors(const std::string& correctLettersPosition);

	void SendGuessedWordToValidationCheck(network::ClientInterace& client);

	void InformServerAboutDisconnection(network::ClientInterace& client);

	std::string GetWordDrawnByServer();

	void DeleteLeastTypedCharacter();


	Game::game_state GetGameState();
	std::vector<Letter>& GetLetters();

	


};