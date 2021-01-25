#pragma once

#include <vector>
#include "Block.h"

class Collider
{
public:
	Collider();
	Collider(sf::Vector2u window);

	/*Add to collider*/
	void addObject(Block object);
	void addPlayer(Block player);

	/*Collisions*/
	void run();

	/*Draw Objects and Players*/
	void drawObjects(sf::RenderWindow &window);
	void updatePointers();

	/*Movement of Player*/
	void movePlayer(bool up, bool down, bool left, bool right, bool sprinting, bool crouching, double elapsed, int index);

	/*Update and get Collider Info*/
	void setGravity(bool on);
	void getGravity();

private:

	/*Collisions*/
	bool crateCollision(Block &movingObject);
	bool borderCollision(sf::RectangleShape &object, sf::Vector2u window);
	bool canMove(Block &movingObject);
	bool isFalling(Block movingObject);

	/*Information*/
	double elapsed;
	bool gravity;
	std::vector<Block> objects;
	std::vector<Block> players;
	sf::Vector2u screenSize;

};

