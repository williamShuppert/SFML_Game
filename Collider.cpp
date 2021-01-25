#include "Collider.h"

Collider::Collider() {
	gravity = false;
}

Collider::Collider(sf::Vector2u window) {
	gravity = false;
	screenSize = window;
}

void Collider::addObject(Block object) {
	// FIX THIS: if something gets removed from list then something is added there will be a shared id between to objects resulting in error
	object.id = objects.size();
	if (object.pushable) objects.push_back(object);
	else objects.insert(objects.begin(), object); // places unpushable objects in the front so they are checked first in the collider
}

void Collider::addPlayer(Block player) {
	// FIX THIS: if the ids change for the objects there will be no way to track which object is the player to update the information on it
	player.id = objects.size();
	players.push_back(player);
	if (player.pushable) objects.push_back(player);
	else objects.insert(objects.begin(), player); // places unpushable objects in the front so they are checked first in the collider
}

void Collider::drawObjects(sf::RenderWindow &window) {
	for (int i = 0; i != objects.size(); i++)
	{
		window.draw(objects[i].shape);
	}
}

void Collider::updatePointers() {
	for (int i = 0; i != objects.size(); i++)
	{
		if (objects[i].textureLocation != "") {
			objects[i].texture.loadFromFile(objects[i].textureLocation);
			objects[i].shape.setTexture(&objects[i].texture);
		}
	}
}

void Collider::movePlayer(bool up, bool down, bool left, bool right, bool sprinting, bool crouching, double elapsed, int index) {

	for (int i = 0; i != objects.size(); i++)
	{
		if (objects[i].id == players[index].id) players[index] = objects[i];
	}

	float speed = players[index].baseSpeed * elapsed;
	if (sprinting) speed = players[index].sprintSpeed * elapsed;
	if (crouching) speed = players[index].crouchSpeed * elapsed;
	if (left) { players[index].shape.move(-speed, 0.0f); }
	if (right) { players[index].shape.move(speed, 0.0f); }
	if (down && !gravity) { players[index].shape.move(0.0f, speed); }
	if (up && !gravity) { players[index].shape.move(0.0f, -speed); }
	if (up && gravity && !players[index].falling) { players[index].jumping = true; }

	for (int i = 0; i != objects.size(); i++)
	{
		if (objects[i].id == players[index].id) objects[i] = players[index];
	}
}

void Collider::setGravity(bool on) {
	gravity = on;
}

bool Collider::crateCollision(Block &movingObject) {
	//movingObject.falling = true;
	for (int i = 0; i != objects.size(); i++) {
		if (objects[i].id != movingObject.id) {
			if (movingObject.shape.getGlobalBounds().intersects(objects[i].shape.getGlobalBounds())) {
				if (abs(movingObject.shape.getPosition().x - objects[i].shape.getPosition().x) > abs(movingObject.shape.getPosition().y - objects[i].shape.getPosition().y)) { // move left/right
					if (movingObject.shape.getPosition().x - objects[i].shape.getPosition().x < 0) { // move right
						if (objects[i].pushable == false) {
							movingObject.shape.setPosition(objects[i].shape.getPosition().x - movingObject.shape.getSize().x, movingObject.shape.getPosition().y);
							return false;
						}
						objects[i].shape.move(movingObject.shape.getSize().x - (objects[i].shape.getPosition().x - movingObject.shape.getPosition().x), 0);

						if (canMove(objects[i]) == false) {
							movingObject.shape.setPosition(objects[i].shape.getPosition().x - movingObject.shape.getSize().x, movingObject.shape.getPosition().y);
							return false;
						}
					}
					else { // move left
						if (objects[i].pushable == false) {
							movingObject.shape.setPosition(objects[i].shape.getPosition().x + movingObject.shape.getSize().x, movingObject.shape.getPosition().y);
							return false;
						}
						objects[i].shape.move(-(objects[i].shape.getPosition().x + objects[i].shape.getSize().x - movingObject.shape.getPosition().x), 0);
						if (canMove(objects[i]) == false) {
							movingObject.shape.setPosition(objects[i].shape.getPosition().x + movingObject.shape.getSize().x, movingObject.shape.getPosition().y);
							return false;
						}
					}
				}
				else { // move up/down
					if (movingObject.shape.getPosition().y - objects[i].shape.getPosition().y < 0) { // move up
						if (objects[i].pushable == false) {
							movingObject.shape.setPosition(movingObject.shape.getPosition().x, objects[i].shape.getPosition().y - movingObject.shape.getSize().y);
							//movingObject.falling = false;
							return false;
						}
						//movingObject.falling = true;
						objects[i].shape.move(0, movingObject.shape.getSize().y - (objects[i].shape.getPosition().y - movingObject.shape.getPosition().y));
						if (canMove(objects[i]) == false) {
							//movingObject.falling = false;
							movingObject.shape.setPosition(movingObject.shape.getPosition().x, objects[i].shape.getPosition().y - movingObject.shape.getSize().y);
							return false;
						}
					}
					else { // move down
						if (objects[i].pushable == false) {
							movingObject.jumping = false;
							movingObject.falling = true;
							movingObject.shape.setPosition(movingObject.shape.getPosition().x, objects[i].shape.getPosition().y + movingObject.shape.getSize().y);
							return false;
						}
						objects[i].shape.move(0, -(objects[i].shape.getPosition().y + objects[i].shape.getSize().y - movingObject.shape.getPosition().y));
						if (canMove(objects[i]) == false) {
							movingObject.jumping = false;
							movingObject.falling = true;
							movingObject.shape.setPosition(movingObject.shape.getPosition().x, objects[i].shape.getPosition().y + movingObject.shape.getSize().y);
							return false;
						}
					}
				}
			}
		}
	}
}

bool Collider::borderCollision(sf::RectangleShape &object, sf::Vector2u window) {
	bool hitWall = false;
	if (object.getPosition().y < 0) {
		object.setPosition(object.getPosition().x, 0);
		hitWall = true;
	}
	if (object.getPosition().y + object.getSize().y > window.y) {
		object.setPosition(object.getPosition().x, window.y - object.getSize().y);
		hitWall = true;
	}
	if (object.getPosition().x < 0) {
		object.setPosition(0, object.getPosition().y);
		hitWall = true;
	}
	if (object.getPosition().x + object.getSize().x > window.x) {
		object.setPosition(window.x - object.getSize().x, object.getPosition().y);
		hitWall = true;
	}
	return !hitWall;
}


bool Collider::canMove(Block &movingObject)	{
	bool hasBeenFalse = false;
	bool canMove = true;
	canMove = borderCollision(movingObject.shape, screenSize);
	if (!canMove) hasBeenFalse = true;
	canMove = crateCollision(movingObject);
	if (!canMove) hasBeenFalse = true;
	return !hasBeenFalse;
}

bool Collider::isFalling(Block movingObject)
{
	movingObject.falling = true;
	movingObject.shape.move(0 , 5);
	for (int i = 0; i != objects.size(); i++) {
		if (objects[i].id != movingObject.id) {
			if (movingObject.shape.getGlobalBounds().intersects(objects[i].shape.getGlobalBounds())) {
				return false;
			}
		}
	}
	return true;
}

void Collider::run() {
	if (gravity == false) {
		for (int i = 0; i != players.size(); i++)
		{
			for (int x = 0; x != objects.size(); x++)
			{
				if (objects[x].id == players[i].id) canMove(objects[x]);
			}
		}

		for (int i = 0; i != players.size(); i++)
		{
			canMove(players[i]);
		}
	}
	else {
		for (int i = 0; i != players.size(); i++)
		{
			canMove(players[i]);
		}

		for (int i = 0; i != objects.size(); i++)
		{
			objects[i].falling = isFalling(objects[i]);
			if (objects[i].falling == false && !objects[i].jumping) objects[i].jumping = false;
			if (objects[i].jumping) { objects[i].jump(); }
			if (objects[i].pushable == true && objects[i].falling == true && objects[i].jumping == false) {
				objects[i].shape.move(0, 5);
				if (canMove(objects[i]) == false) objects[i].falling = false;
			}
			canMove(objects[i]);
		}


	}
}



//#include "Collider.h"
//
//Collider::Collider() {
//	gravity = false;
//}
//
//Collider::Collider(sf::Vector2u window) {
//	gravity = false;
//	screenSize = window;
//}
//
//void Collider::addObject(Block object) {
//	// FIX THIS: if something gets removed from list then something is added there will be a shared id between to objects resulting in error
//	object.id = objects.size();
//	if (object.pushable) objects.push_back(object);
//	else objects.insert(objects.begin(), object); // places unpushable objects in the front so they are checked first in the collider
//}
//
//void Collider::addPlayer(Block player) {
//	// FIX THIS: if the ids change for the objects there will be no way to track which object is the player to update the information on it
//	player.id = objects.size();
//	players.push_back(player);
//	if (player.pushable) objects.push_back(player);
//	else objects.insert(objects.begin(), player); // places unpushable objects in the front so they are checked first in the collider
//}
//
//void Collider::drawObjects(sf::RenderWindow &window) {
//	for (int i = 0; i != objects.size(); i++)
//	{
//		window.draw(objects[i].shape);
//	}
//}
//
//void Collider::updatePointers() {
//	for (int i = 0; i != objects.size(); i++)
//	{
//		if (objects[i].textureLocation != "") {
//			objects[i].image.loadFromFile(objects[i].textureLocation);
//			objects[i].texture.loadFromImage(objects[i].image);
//			objects[i].shape.setTexture(&objects[i].texture);
//		}
//	}
//}
//
//void Collider::movePlayer(bool up, bool down, bool left, bool right, bool sprinting, bool crouching, double elapsed, int index) {
//
//	for (int i = 0; i != objects.size(); i++)
//	{
//		if (objects[i].id == players[index].id) players[index] = objects[i];
//	}
//
//	float speed = players[index].baseSpeed * elapsed;
//	if (sprinting) speed = players[index].sprintSpeed * elapsed;
//	if (crouching) speed = players[index].crouchSpeed * elapsed;
//	if (left) {
//		players[index].image.flipHorizontally();
//		players[index].texture.loadFromImage(players[index].image);
//		players[index].shape.move(-speed, 0.0f); /*players[index].shape.setTexture(&players[index].textureLocation);*/
//	}
//	if (right) { players[index].shape.move(speed, 0.0f); }
//	if (down && !gravity) { players[index].shape.move(0.0f, speed); }
//	if (up && !gravity) { players[index].shape.move(0.0f, -speed); }
//	if (up && gravity && !players[index].falling) { players[index].jumping = true; }
//
//	for (int i = 0; i != objects.size(); i++)
//	{
//		if (objects[i].id == players[index].id) objects[i] = players[index];
//	}
//}
//
//void Collider::setGravity(bool on) {
//	gravity = on;
//}
//
//bool Collider::crateCollision(Block &movingObject) {
//	//movingObject.falling = true;
//	for (int i = 0; i != objects.size(); i++) {
//		if (objects[i].id != movingObject.id) {
//			if (movingObject.shape.getGlobalBounds().intersects(objects[i].shape.getGlobalBounds())) {
//				if (abs(movingObject.shape.getPosition().x - objects[i].shape.getPosition().x) > abs(movingObject.shape.getPosition().y - objects[i].shape.getPosition().y)) { // move left/right
//					if (movingObject.shape.getPosition().x - objects[i].shape.getPosition().x < 0) { // move right
//						if (objects[i].pushable == false) {
//							movingObject.shape.setPosition(objects[i].shape.getPosition().x - movingObject.shape.getSize().x, movingObject.shape.getPosition().y);
//							return false;
//						}
//						objects[i].shape.move(movingObject.shape.getSize().x - (objects[i].shape.getPosition().x - movingObject.shape.getPosition().x), 0);
//
//						if (canMove(objects[i]) == false) {
//							movingObject.shape.setPosition(objects[i].shape.getPosition().x - movingObject.shape.getSize().x, movingObject.shape.getPosition().y);
//							return false;
//						}
//					}
//					else { // move left
//						if (objects[i].pushable == false) {
//							movingObject.shape.setPosition(objects[i].shape.getPosition().x + movingObject.shape.getSize().x, movingObject.shape.getPosition().y);
//							return false;
//						}
//						objects[i].shape.move(-(objects[i].shape.getPosition().x + objects[i].shape.getSize().x - movingObject.shape.getPosition().x), 0);
//						if (canMove(objects[i]) == false) {
//							movingObject.shape.setPosition(objects[i].shape.getPosition().x + movingObject.shape.getSize().x, movingObject.shape.getPosition().y);
//							return false;
//						}
//					}
//				}
//				else { // move up/down
//					if (movingObject.shape.getPosition().y - objects[i].shape.getPosition().y < 0) { // move up
//						if (objects[i].pushable == false) {
//							movingObject.shape.setPosition(movingObject.shape.getPosition().x, objects[i].shape.getPosition().y - movingObject.shape.getSize().y);
//							//movingObject.falling = false;
//							return false;
//						}
//						//movingObject.falling = true;
//						objects[i].shape.move(0, movingObject.shape.getSize().y - (objects[i].shape.getPosition().y - movingObject.shape.getPosition().y));
//						if (canMove(objects[i]) == false) {
//							//movingObject.falling = false;
//							movingObject.shape.setPosition(movingObject.shape.getPosition().x, objects[i].shape.getPosition().y - movingObject.shape.getSize().y);
//							return false;
//						}
//					}
//					else { // move down
//						movingObject.jumping = false;
//						movingObject.falling = true;
//						if (objects[i].pushable == false) {
//							movingObject.shape.setPosition(movingObject.shape.getPosition().x, objects[i].shape.getPosition().y + movingObject.shape.getSize().y);
//							printf("Hit");
//							return false;
//						}
//						objects[i].shape.move(0, -(objects[i].shape.getPosition().y + objects[i].shape.getSize().y - movingObject.shape.getPosition().y));
//						if (canMove(objects[i]) == false) {
//							movingObject.shape.setPosition(movingObject.shape.getPosition().x, objects[i].shape.getPosition().y + movingObject.shape.getSize().y);
//							return false;
//						}
//					}
//				}
//			}
//		}
//	}
//}
//
//bool Collider::borderCollision(sf::RectangleShape &object, sf::Vector2u window) {
//	bool hitWall = false;
//	if (object.getPosition().y < 0) {
//		object.setPosition(object.getPosition().x, 0);
//		hitWall = true;
//	}
//	if (object.getPosition().y + object.getSize().y > window.y) {
//		object.setPosition(object.getPosition().x, window.y - object.getSize().y);
//		hitWall = true;
//	}
//	if (object.getPosition().x < 0) {
//		object.setPosition(0, object.getPosition().y);
//		hitWall = true;
//	}
//	if (object.getPosition().x + object.getSize().x > window.x) {
//		object.setPosition(window.x - object.getSize().x, object.getPosition().y);
//		hitWall = true;
//	}
//	return !hitWall;
//}
//
//
//bool Collider::canMove(Block &movingObject) {
//	bool hasBeenFalse = false;
//	bool canMove = true;
//	canMove = borderCollision(movingObject.shape, screenSize);
//	if (!canMove) hasBeenFalse = true;
//	canMove = crateCollision(movingObject);
//	if (!canMove) hasBeenFalse = true;
//	return !hasBeenFalse;
//}
//
//bool Collider::isFalling(Block movingObject)
//{
//	movingObject.falling = true;
//	movingObject.shape.move(0, 5);
//	for (int i = 0; i != objects.size(); i++) {
//		if (objects[i].id != movingObject.id) {
//			if (movingObject.shape.getGlobalBounds().intersects(objects[i].shape.getGlobalBounds())) {
//				return false;
//			}
//		}
//	}
//	return true;
//}
//
//void Collider::run() {
//	if (gravity == false) {
//		for (int i = 0; i != players.size(); i++)
//		{
//			for (int x = 0; x != objects.size(); x++)
//			{
//				if (objects[x].id == players[i].id) canMove(objects[x]);
//			}
//		}
//
//		for (int i = 0; i != players.size(); i++)
//		{
//			canMove(players[i]);
//		}
//	}
//	else {
//		for (int i = 0; i != players.size(); i++)
//		{
//			canMove(players[i]);
//		}
//
//		for (int i = 0; i != objects.size(); i++)
//		{
//			objects[i].falling = isFalling(objects[i]);
//			if (objects[i].falling == false && !objects[i].jumping) objects[i].jumping = false;
//			if (objects[i].jumping) { objects[i].jump(); }
//			if (objects[i].pushable == true && objects[i].falling == true && objects[i].jumping == false) {
//				objects[i].shape.move(0, 5);
//				if (canMove(objects[i]) == false) objects[i].falling = false;
//			}
//			canMove(objects[i]);
//		}
//
//
//	}
//}



