#include "Label.h"

/*Constructors*/
Label::Label() {
	/*Box size and position*/
	shape.setPosition(sf::Vector2f(0,0));
	shape.setSize(sf::Vector2f(100, 50));

	/*Colors*/
	this->outLineColor = sf::Color(150, 150, 150);
	this->color = sf::Color(192, 192, 192);
	this->outLineThickness = 3;
	this->textColor = sf::Color::Black;

	this->font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
	fontPath = "C:\\Windows\\Fonts\\arial.ttf";
	this->text.setFont(this->font);
	this->text.setString("Lable");
	this->text.setFillColor(textColor);
	this->text.setPosition(sf::Vector2f((this->shape.getSize().x / 2) - (this->text.getLocalBounds().width / 2), (this->shape.getSize().y / 2) - (18)));//this->text.getLocalBounds().height

	// update looks
	shape.setFillColor(color);
	shape.setOutlineThickness(3);
	shape.setOutlineColor(outLineColor);
}
Label::Label(sf::Vector2f position, sf::Vector2f size, std::string text, bool centerText, sf::Color textColor, sf::Color color, sf::Color outLineColor, int outlineThickness, std::string font) {
	/*Box size and position*/
	shape.setPosition(position);
	shape.setSize(size);

	/*Colors*/
	this->outLineColor = outLineColor;
	this->color = color;
	this->outLineThickness = outlineThickness;
	this->textColor = textColor;

	this->font.loadFromFile(font);
	fontPath = font;
	this->text.setFont(this->font);
	this->text.setString(text);
	this->text.setFillColor(textColor);
	if (centerText) this->text.setPosition(sf::Vector2f(position.x + (this->shape.getSize().x / 2) - (this->text.getLocalBounds().width / 2), position.y + (this->shape.getSize().y / 2) - (18)));//this->text.getLocalBounds().height
	else this->text.setPosition(position);

	// update looks
	shape.setFillColor(color);
	shape.setOutlineThickness(outlineThickness);
	shape.setOutlineColor(outLineColor);
}

/*Font and fontPath*/
void Label::setFont(std::string fontPath) {
	this->font.loadFromFile(fontPath);
	this->fontPath = fontPath;
	this->text.setFont(this->font);
}
std::string Label::getFontPath() {
	return fontPath;
}