#pragma once

#include "SFML/Graphics.hpp"
#include "Label.h"
#include <string>

class TextBox : public Label
{
public:
	/*Constructors*/
	TextBox();
	TextBox(
		sf::Vector2f position,
		sf::Vector2f size,
		std::string defaultString = "",
		sf::Color color = sf::Color::White,
		sf::Color textColor = sf::Color::Black,
		int outlineThickness = 3,
		sf::Color outLineColor = sf::Color(150, 150, 150),
		sf::Color selectedOutlineColor = sf::Color(105, 176, 250),
		std::string font = "C:\\Windows\\Fonts\\arial.ttf"
	);

	/*Cursor*/
	sf::RectangleShape cursor;

	/*Update Looks*/
	bool update(sf::Vector2f mousePosition, bool mouseHold);

	bool isSelected();
	void setSelected(bool change);

private:
	/*Information*/
	sf::Color selectedOutlineColor; // colors of the button in different states
	bool selected;
};

