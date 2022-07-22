#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Letter : public sf::RectangleShape
{
protected:

	sf::Color mColor;
	sf::Color mGreenColor;
	sf::Color mYellowColor;
	sf::Color mRedColor;

	sf::Text mUIText;

	

public:

	explicit Letter(int x = 0, int y = 0, int width = 50, int height = 50);
	/*Letter(const unsigned int& x, const unsigned int& y, const sf::Font& font, 
		unsigned int fontSize, unsigned int width, unsigned int height);*/
	virtual ~Letter();
	
	void SetGreenColor();
	void SetYellowColor();
	void SetRedColor();

	void InitLetterDisplay(int x, int y, int width, int height);
	void InitTextDisplay(const sf::Font&, unsigned int fontSize, sf::Color color, std::string text, const sf::Vector2f& textPosition);
	void SetTextDisplay(std::string text);

	sf::Text& GetTextToDisplay();

};