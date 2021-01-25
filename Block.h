#pragma once

#include "SFML/Graphics.hpp"
#include <string>

class Block
{
public:				
	Block();																																								// default		
	Block(sf::Vector2f position, sf::Vector2f size, bool pushable, sf::Color color);																						// crate or wall, no texture
	Block(sf::Vector2f position, sf::Vector2f size, bool pushable, std::string textureLocation);																			// crate or wall, with texture
	Block(sf::Vector2f position, sf::Vector2f size, bool pushable, float baseSpeed, float sprintSpeed, float crouchSpeed, sf::Color color);									// character, no texture
	Block(sf::Vector2f position, sf::Vector2f size, bool pushable, float baseSpeed, float sprintSpeed, float crouchSpeed, std::string textureLocation);						// character, with texture
	
	/*Main Component*/
	sf::RectangleShape shape;
	sf::Texture texture;

	/*Speed*/
	float baseSpeed;
	float crouchSpeed;
	float sprintSpeed;

	/*Movement*/
	void jump();

	/*Information*/
	std::string textureLocation;
	bool pushable;
	bool falling;
	bool jumping;
	float jumpStartPos;

	// bool destoryOnImpact;
	int id;
private:
};

