#pragma once

#include "SFML/Graphics.hpp"

class Label
{
public:
	Label();
	Label( // every thing
		sf::Vector2f position,
		sf::Vector2f size,
		std::string text = "",
		bool centerText = true,
		sf::Color textColor = sf::Color::Black,
		sf::Color color = sf::Color(192, 192, 192),
		sf::Color outLineColor = sf::Color(150, 150, 150),
		int outlineThickness = 3,
		std::string font = "C:\\Windows\\Fonts\\arial.ttf"
	);

	/*Main Components*/
	sf::RectangleShape shape;
	sf::Text text;
	sf::Font font;

	void setFont(std::string fontPath); // set font path by passing a string
	std::string getFontPath(); // returns a string of the file location of the font

protected:
	std::string fontPath; // the font path as a string to be used when added to GUI Manager because pointer would be destroyed
	sf::Color color, outLineColor, textColor; // colors of the button in different states
	int outLineThickness;

};

