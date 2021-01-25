#include "Button.h"

/*Constructors*/
Button::Button() {
	/*button size and postion*/
	shape.setPosition(sf::Vector2f(0,0));
	shape.setSize(sf::Vector2f(100,50));

	/*button colors for each state*/
	this->color = sf::Color::White;
	this->hoverColor = sf::Color(192, 192, 192);
	this->clickColor = sf::Color(150, 150, 150);
	this->outLineColor = sf::Color(150, 150, 150);
	this->outLineThickness = 5;

	/*Default text settings*/
	fontPath = "C:\\Windows\\Fonts\\arial.ttf";
	this->font.loadFromFile(this->fontPath);
	this->text.setFont(this->font);
	this->text.setString("");
	this->text.setFillColor(sf::Color::Black);
}
Button::Button(sf::Vector2f position, sf::Vector2f size, std::string text, bool centerText, sf::Color textColor, sf::Color color, sf::Color outLineColor, int outlineThickness, sf::Color hoverColor, sf::Color clickColor, std::string font) {
	/*button size and postion*/
	shape.setPosition(position);
	shape.setSize(size);

	/*text*/
	this->font.loadFromFile(font);
	fontPath = font;
	this->text.setFont(this->font);
	this->text.setString(text);
	this->text.setFillColor(textColor);
	if (centerText) this->text.setPosition(sf::Vector2f(position.x + (this->shape.getSize().x / 2) - (this->text.getLocalBounds().width / 2), position.y + (this->shape.getSize().y / 2) - (18)));//this->text.getLocalBounds().height
	else this->text.setPosition(position);

	/*button colors for each state*/
	this->color = color;
	this->hoverColor = hoverColor;
	this->clickColor = clickColor;
	this->outLineColor = outLineColor;
	this->outLineThickness = outlineThickness;
}

/*Other*/
int Button::update(sf::Vector2f mousePosition, bool mouseHold) {
	// over and clicked
	shape.setOutlineColor(outLineColor);
	shape.setOutlineThickness(outLineThickness);
	if (shape.getGlobalBounds().contains(mousePosition) && mouseHold) {
		shape.setFillColor(clickColor);
		return 2;
	} else if (shape.getGlobalBounds().contains(mousePosition)) {
		shape.setFillColor(hoverColor);
		return 1;
	}
	else {
		shape.setFillColor(color);
		return 0;
	}
}
sf::Color Button::getIdleColor() {
	return color;
}
