#include <SFML\Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "TextBox.h"
#include "GUI_Manager.h"
#include "Collider.h"
#include "Block.h"

using namespace sf;

void setUpWidgets(GUI_Manager &GUI);
void GUI_Events(bool onPress, GUI_Manager &GUI, RenderWindow &window);

int main() {

	// Allows me to get time between frames
	Clock clock;
	Time time;
	double elapsed;

	/*Setup*/
	GUI_Manager GUI;
	RenderWindow window(VideoMode(1440, 900), "The Title of the Window");
	Collider collider(window.getSize());
	collider.setGravity(true);

	collider.addObject(Block(sf::Vector2f(50, 100), sf::Vector2f(50, 50), true, "Textures/Crate/testCrate.png" ));
	collider.addObject(Block(sf::Vector2f(50, 200), sf::Vector2f(50, 50), true, "Textures/Crate/testCrate.png" ));
	collider.addObject(Block(sf::Vector2f(50, 300), sf::Vector2f(50, 50), true, "Textures/Crate/testCrate.png" ));
	collider.addObject(Block(sf::Vector2f(50, 400), sf::Vector2f(50, 50), true, "Textures/Crate/testCrate.png" ));
	collider.addObject(Block(sf::Vector2f(50, 450), sf::Vector2f(50, 50), true, "Textures/Crate/testCrate.png"));
	collider.addObject(Block(sf::Vector2f(50, 400), sf::Vector2f(50, 50), true, "Textures/Crate/testCrate.png"));
	collider.addObject(Block(sf::Vector2f(50, 400), sf::Vector2f(50, 50), true, "Textures/Crate/testCrate.png"));
	collider.addObject(Block(sf::Vector2f(50, 400), sf::Vector2f(50, 50), true, "Textures/Crate/testCrate.png"));
	collider.addObject(Block(sf::Vector2f(50, 400), sf::Vector2f(50, 50), true, "Textures/Crate/testCrate.png"));

	for (int i = 0; i < 20; i++)
	{
		collider.addObject(Block(sf::Vector2f( i * 50, 450), sf::Vector2f(50, 50), false, "Textures/Wall/testWall.png"));
	}

	collider.addObject(Block(sf::Vector2f(250, 700), sf::Vector2f(50, 50), false, "Textures/Wall/testWall.png"));

	collider.addPlayer(Block(sf::Vector2f(0, 0), sf::Vector2f(45, 50), true, 200, 300, 100, "Textures/Characters/Player/mario.png" ));
	//collider.addPlayer(Block(sf::Vector2f(0, 0), sf::Vector2f(45, 50), true, 200, 300, 100, sf::Color::Red));
	collider.addPlayer(Block(sf::Vector2f(500, 500), sf::Vector2f(28, 55), true, 200, 300, 100, "Textures/Characters/Player/luigi.png" ));

	collider.updatePointers();

	/*Adding GUI Elements*/
	setUpWidgets(GUI);

	while (window.isOpen()) {
		// Get time between frames
		time = clock.getElapsedTime();
		elapsed = time.asSeconds();
		clock.restart();

		GUI.updateGUI(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y)); // updates using general mouse position

		/*Events*/
		Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case Event::Closed:
				window.close();
				break;
			case Event::TextEntered:
				GUI.typeInTextBox(evnt.text.unicode);
				if (evnt.text.unicode < 128)	printf("%c", evnt.text.unicode);
				break;
			case Event::MouseButtonPressed:
				GUI.deselectTextboxes(); // deselect all textboxes
				if (Mouse::isButtonPressed(Mouse::Left)) {
					GUI.setMouseHold(true); // mouse is being held down
					/*On Press*/
					GUI_Events(true, GUI, window);
					break;
				}
			case Event::MouseButtonReleased:
				/*On Release*/
				GUI_Events(false, GUI, window);
				GUI.setMouseHold(false); // mouse is not being held down anymore	
				break;
			}

		}

		/*Player Movement*/
		collider.movePlayer(Keyboard::isKeyPressed(Keyboard::Key::W), Keyboard::isKeyPressed(Keyboard::Key::S), Keyboard::isKeyPressed(Keyboard::Key::A), Keyboard::isKeyPressed(Keyboard::Key::D), Keyboard::isKeyPressed(Keyboard::Key::LShift), Keyboard::isKeyPressed(Keyboard::Key::LControl), elapsed, 0);
		collider.movePlayer(Keyboard::isKeyPressed(Keyboard::Key::Up), Keyboard::isKeyPressed(Keyboard::Key::Down), Keyboard::isKeyPressed(Keyboard::Key::Left), Keyboard::isKeyPressed(Keyboard::Key::Right), Keyboard::isKeyPressed(Keyboard::Key::LShift), Keyboard::isKeyPressed(Keyboard::Key::LControl), elapsed, 1);

		/*Running the Collider*/
		collider.run();

		/*Update Window*/
		window.clear();

		GUI.drawGUI(window); // draws all GUI elements

		collider.drawObjects(window); // draws everything in collider

		window.display();

	}
	//system("pause");
	return 0;
}

void setUpWidgets(GUI_Manager &GUI) {

}

void GUI_Events(bool onPress, GUI_Manager &GUI, RenderWindow &window) {
	if (onPress) {
		switch (GUI.updateButtons((Vector2f)Mouse::getPosition(window))) {
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		}
	}
	else {
		
		switch (GUI.updateButtons((Vector2f)Mouse::getPosition(window))) {
		case 0:
		{

			break;
		}
		case 1:

			break;
		case 2:

			break;
		}
	}
}