#include "Block.h"



Block::Block() {
	shape.setFillColor(sf::Color::White);
	shape.setSize(sf::Vector2f(50, 50));
	shape.setPosition(sf::Vector2f(0, 0));
	pushable = true;
	baseSpeed = 0;
	sprintSpeed = 0;
	crouchSpeed = 0;
	textureLocation = "";
	falling = true;
	jumping = false;
	jumpStartPos = 0;
}

Block::Block(sf::Vector2f position, sf::Vector2f size, bool pushable, sf::Color color) {
	shape.setFillColor(color);
	shape.setSize(size);
	shape.setPosition(position);
	this->pushable = pushable;
	baseSpeed = 0;
	sprintSpeed = 0;
	crouchSpeed = 0;
	textureLocation = "";
	falling = true;
	jumping = false;
	jumpStartPos = 0;
}

Block::Block(sf::Vector2f position, sf::Vector2f size, bool pushable, std::string textureLocation) {
	shape.setSize(size);
	shape.setPosition(position);
	this->pushable = pushable;
	baseSpeed = 0;
	sprintSpeed = 0;
	crouchSpeed = 0;
	this->textureLocation = textureLocation;
	falling = true;
	jumping = false;
	jumpStartPos = 0;
}

Block::Block(sf::Vector2f position, sf::Vector2f size, bool pushable, float baseSpeed, float sprintSpeed, float crouchSpeed, sf::Color color) {
	shape.setFillColor(color);
	shape.setSize(size);
	shape.setPosition(position);
	this->pushable = pushable;
	this->baseSpeed = baseSpeed;
	this->sprintSpeed = sprintSpeed;
	this->crouchSpeed = crouchSpeed;
	this->textureLocation = "";
	falling = true;
	jumping = false;
	jumpStartPos = 0;
}

Block::Block(sf::Vector2f position, sf::Vector2f size, bool pushable, float baseSpeed, float sprintSpeed, float crouchSpeed, std::string textureLocation) {
	shape.setSize(size);
	shape.setPosition(position);
	this->pushable = pushable;
	this->baseSpeed = baseSpeed;
	this->sprintSpeed = sprintSpeed;
	this->crouchSpeed = crouchSpeed;
	this->textureLocation = textureLocation;
	falling = true;
	jumping = false;
	jumpStartPos = 0;
}

void Block::jump() {
	if (jumpStartPos == 0) jumpStartPos = shape.getPosition().y;
	if (jumpStartPos - shape.getPosition().y < 125)	shape.move(0, -5);
	else { jumping = false; jumpStartPos = 0; falling = true; }
}


