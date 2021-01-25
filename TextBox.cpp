#include "TextBox.h"

/*Constructors*/
TextBox::TextBox() {

	/*Box size and position*/
	shape.setPosition(sf::Vector2f(0, 0));
	shape.setSize(sf::Vector2f(200, 50));

	/*Color and font*/
	this->outLineColor = sf::Color(150, 150, 150);
	this->selectedOutlineColor = sf::Color(105, 176, 250);
	this->color = sf::Color::Black;
	this->outLineThickness = 3;

	this->font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
	fontPath = "C:\\Windows\\Fonts\\arial.ttf";
	this->text.setFont(this->font);
	this->text.setString("A");
	this->text.setFillColor(textColor);
	text.setPosition(sf::Vector2f(outLineThickness, (this->shape.getSize().y / 2) - (this->text.getLocalBounds().height)));
	this->text.setString("");
	cursor.setPosition(sf::Vector2f(text.getPosition().x + text.getGlobalBounds().width + shape.getOutlineThickness(), text.getPosition().y));
	cursor.setSize(sf::Vector2f(2, shape.getSize().y - shape.getOutlineThickness() * 2));
	cursor.setFillColor(sf::Color::Black);

	// update looks
	shape.setFillColor(color);
	shape.setOutlineThickness(this->outLineThickness);
	shape.setOutlineColor(outLineColor);

	selected = false;
}
TextBox::TextBox(sf::Vector2f position, sf::Vector2f size, std::string defaultString, sf::Color color, sf::Color textColor, int outlineThickness, sf::Color outLineColor, sf::Color selectedOutlineColor, std::string font) {
	
	/*Box size and position*/
	shape.setPosition(position);
	shape.setSize(size);

	/*Colors*/
	this->outLineColor = outLineColor;
	this->selectedOutlineColor = selectedOutlineColor;
	this->color = color;
	this->outLineThickness = outlineThickness;

	this->font.loadFromFile(font);
	fontPath = font;
	this->text.setFont(this->font);
	this->text.setString("A");
	this->text.setFillColor(textColor);
	text.setPosition(sf::Vector2f(position.x + outLineThickness, position.y + (this->shape.getSize().y / 2) - (this->text.getLocalBounds().height)));
	this->text.setString(defaultString);
	cursor.setPosition(sf::Vector2f(text.getPosition().x + text.getGlobalBounds().width + shape.getOutlineThickness(), text.getPosition().y));
	cursor.setSize(sf::Vector2f(2, shape.getSize().y - shape.getOutlineThickness() * 2));
	cursor.setFillColor(sf::Color::Black);

	// update looks
	shape.setFillColor(color);
	shape.setOutlineThickness(outlineThickness);
	shape.setOutlineColor(outLineColor);

	selected = false;
}

/*Other*/
bool TextBox::update(sf::Vector2f mousePosition, bool mouseHold) {

	if (shape.getGlobalBounds().contains(mousePosition) && mouseHold) {
		shape.setOutlineColor(selectedOutlineColor);
		cursor.setPosition(sf::Vector2f(text.getPosition().x + text.getGlobalBounds().width + shape.getOutlineThickness(), text.getPosition().y));
		cursor.setSize(sf::Vector2f(2, shape.getSize().y - shape.getOutlineThickness() * 2));
		cursor.setFillColor(sf::Color::Black);
		return true;
	}
	else if (selected) {
		shape.setOutlineColor(selectedOutlineColor);
		cursor.setPosition(sf::Vector2f(text.getPosition().x + text.getGlobalBounds().width + shape.getOutlineThickness(), text.getPosition().y));
		cursor.setSize(sf::Vector2f(2, shape.getSize().y - shape.getOutlineThickness() * 2));
		cursor.setFillColor(sf::Color::Black);
		return true;
	}
	else {
		shape.setOutlineColor(outLineColor);
		cursor.setFillColor(shape.getFillColor());
	}
	return false;
}
bool TextBox::isSelected()
{
	return selected;
}
void TextBox::setSelected(bool change)
{
	selected = change;
}
