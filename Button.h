#pragma once

#include "SFML/Graphics.hpp"
#include "Label.h"
#include <string>

class Button : public Label {
public:
	/*Constructors*/
	Button(); // default
	Button( // every thing
		sf::Vector2f position,
		sf::Vector2f size,
		std::string text = "",
		bool centerText = true,
		sf::Color textColor = sf::Color::Black,
		sf::Color color = sf::Color::White,
		sf::Color outLineColor = sf::Color(150, 150, 150),
		int outlineThickness = 3,
		sf::Color hoverColor = sf::Color(192, 192, 192),
		sf::Color clickColor = sf::Color(150, 150, 150),
		std::string font = "C:\\Windows\\Fonts\\arial.ttf"
	);

	/*Update*/
	int update(sf::Vector2f mousePosition, bool mouseHold = false); // changes color based on mouse position

	/*Information*/
	sf::Color getIdleColor(); // return idle color


private:
	/*Information*/
	sf::Color hoverColor, clickColor; // colors of the button in different states

};

