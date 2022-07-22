#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Letter.h"


class Renderer
{
private:

	sf::Font mFont;

	const unsigned int WINDOW_WIDTH = 1000;
	const unsigned int WINDOW_HEIGHT = 1000;
	const unsigned int WINDOW_FRAMERATE = 60;

	const unsigned int LETTER_WIDTH = 150;
	const unsigned int LETTER_HEIGHT = 150;

	
	
public:
	Renderer() = delete;
	Renderer(sf::RenderWindow*& window, std::vector<Letter>& letters);

private:

	void InitDisplayedObjects(std::vector<Letter>& letters);
	void InitWindow(sf::RenderWindow*& window);
	
	void InitUserPlayingScreen(std::vector<Letter>& letters);
	void InitVictoryScreen(std::vector<Letter>& letters);
	void InitLostScreen(std::vector<Letter>& letters, std::string victoryWord);

public:


	void LoadFontFromFile();
	void RenderUserPlayingScreen(sf::RenderTarget& target, std::vector<Letter>& letters);
	void RenderVictoryScreen(sf::RenderTarget& target, std::vector<Letter>& letters);
	void RenderDefeatedScreen(sf::RenderTarget& target, std::vector<Letter>& letters, std::string drawnWord);
	void RenderNotInDictionaryScreen(sf::RenderTarget& target, std::vector<Letter>& letters);
	
};