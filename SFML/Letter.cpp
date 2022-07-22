#include "Letter.h"

Letter::Letter(int x, int y, int width, int height) : sf::RectangleShape(),
               mColor(sf::Color::Black), mGreenColor(sf::Color(8, 255, 37)), 
               mYellowColor(sf::Color(248, 197, 30)), mRedColor(sf::Color(224, 60, 27))
{
    InitLetterDisplay(x, y, width, height);
}

//Letter::Sign(const unsigned int& x, const unsigned int& y, const sf::Font& font,
//    unsigned int fontSize = 20, unsigned int width = 40, unsigned int height = 40) :
//            sf::RectangleShape(), x(x), y(y),
//            mWidth(width), mHeight(height),
//            mMainColor(sf::Color::Black)
//{
//    InitSignDisplay();
//    //InitTextDisplay(font, fontSize, mMainColor);
//}

Letter::~Letter()
{
}


void Letter::SetGreenColor()
{
    this->setFillColor(mGreenColor);
}

void Letter::SetYellowColor()
{
    this->setFillColor(mYellowColor);
}

void Letter::SetRedColor()
{
    this->setFillColor(mRedColor);
}

void Letter::InitLetterDisplay(int x, int y, int width, int height)
{
    this->setPosition(x, y);
    this->setFillColor(mColor);
    this->setSize(sf::Vector2f(width, height));
    this->setOutlineThickness(1);
   
}

void Letter::InitTextDisplay(const sf::Font& font, unsigned int fontSize, sf::Color color, std::string text, const sf::Vector2f& textPosition)
{
    mUIText.setFont(font);
    mUIText.setCharacterSize(fontSize);
    mUIText.setFillColor(color);
    mUIText.setString(text);
    mUIText.setPosition(textPosition);
}

void Letter::SetTextDisplay(std::string text)
{
    mUIText.setString(text);
}

sf::Text& Letter::GetTextToDisplay()
{
    return mUIText;
}
