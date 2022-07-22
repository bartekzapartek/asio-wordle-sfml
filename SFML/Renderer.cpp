#include "Renderer.h"
#include <iostream>
#include <sstream>

Renderer::Renderer(sf::RenderWindow*& window, std::vector<Letter>& letters)
{
	InitWindow(window);
	LoadFontFromFile();
	InitDisplayedObjects(letters);
}

void Renderer::InitWindow(sf::RenderWindow*& window)
{
	sf::VideoMode windowMode(WINDOW_WIDTH, WINDOW_HEIGHT);
	window = new sf::RenderWindow(windowMode, "Wordle", sf::Style::Close | sf::Style::Titlebar);
	window->setFramerateLimit(WINDOW_FRAMERATE);
}

void Renderer::InitUserPlayingScreen(std::vector<Letter>& letters)
{
	std::string victory = "victory";
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			std::stringstream sVictory;
			sVictory << victory[(x + y * 5) % 7];
			letters[x + y * 5].SetTextDisplay(sVictory.str());
			letters[x + y * 5].SetGreenColor();
		}
	}
}

void Renderer::InitVictoryScreen(std::vector<Letter>& letters)
{
	std::string victory = "VICTORY";

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			std::stringstream sVictory;
			sVictory << victory[(x + y * 5) % 7];
			letters[x + y * 5].SetTextDisplay(sVictory.str());
			letters[x + y * 5].SetGreenColor();
		}
	}
}

void Renderer::InitLostScreen(std::vector<Letter>& letters, std::string victoryWord)
{
	std::transform(victoryWord.begin(), victoryWord.end(), victoryWord.begin(), [](unsigned char c) { return std::toupper(c); });

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			std::stringstream sVictory;
			sVictory << victoryWord[x];
			letters[x + y * 5].SetTextDisplay(sVictory.str());
			letters[x + y * 5].SetRedColor();
		}
	}
}



void Renderer::InitDisplayedObjects(std::vector<Letter>& letters)
{
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			float moveCenterVectorX = (WINDOW_WIDTH - 5 * (LETTER_WIDTH + 5)) / 2;
			float moveCenterVectorY = (WINDOW_HEIGHT - 5 * (LETTER_HEIGHT + 5)) / 2;
			sf::Vector2f letterPosition(moveCenterVectorX + x * (LETTER_WIDTH + 5),
										moveCenterVectorY + y * (LETTER_HEIGHT + 5));
			sf::Vector2f letterSize(LETTER_WIDTH, LETTER_HEIGHT);
			
			
			sf::Vector2f textPosition(letterPosition.x + 15, letterPosition.y + 5);

			letters[x + y * 5].setSize(letterSize);
		
			letters[x + y * 5].setPosition(letterPosition);
			letters[x + y * 5].setFillColor(sf::Color::Black);
			letters[x + y * 5].InitTextDisplay(mFont, 120, sf::Color::White, "", textPosition);
		}
	}
}

void Renderer::LoadFontFromFile()
{
	mFont.loadFromFile("Fonts/Roboto-Light.ttf");
}

void Renderer::RenderUserPlayingScreen(sf::RenderTarget& target, std::vector<Letter>& letters)
{
	for (auto& letter : letters)
	{
		target.draw(letter);
		target.draw(letter.GetTextToDisplay());
	}
}

void Renderer::RenderVictoryScreen(sf::RenderTarget& target, std::vector<Letter>& letters)
{
	InitVictoryScreen(letters);
	for (auto& letter : letters)
	{
		target.draw(letter);
		target.draw(letter.GetTextToDisplay());
	}
}

void Renderer::RenderDefeatedScreen(sf::RenderTarget& target, std::vector<Letter>& letters, std::string drawnWord)
{
	InitLostScreen(letters, drawnWord);
	for (auto& letter : letters)
	{
		target.draw(letter);
		target.draw(letter.GetTextToDisplay());
	}
}

void Renderer::RenderNotInDictionaryScreen(sf::RenderTarget& target, std::vector<Letter>& letters)
{
	sf::Text notInDictionary;
	notInDictionary.setCharacterSize(50);
	notInDictionary.setFont(mFont);
	notInDictionary.setFillColor(sf::Color::White);
	notInDictionary.setString("not in dictionary");
	notInDictionary.setPosition(WINDOW_WIDTH / 3, 30);

	for (auto& letter : letters)
	{
		target.draw(letter);
		target.draw(letter.GetTextToDisplay());
	}

	target.draw(notInDictionary);
}
