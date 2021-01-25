#pragma once

#include "SFML/Graphics.hpp"
#include "Label.h"
#include "Button.h"
#include "TextBox.h"
#include <vector>

class GUI_Manager
{
public:
	/*Constructor*/
	GUI_Manager();

	/*Mouse Information*/
	void setMouseHold(bool state); // sets the state of the mouse, being held in or not
	bool getMouseHold(); // returns if the mouse is being held

	/*Adding Elements*/
	void addButton(Button button);
	void addTextBox(TextBox textbox);
	void addLabel(Label label);

	/*Get Elements*/
	Button getButton(int index);
	TextBox getTextbox(int index);
	Label getLabel(int index);
	
	/*Set Elements*/
	void setElement(Button button, int index);
	void setElement(TextBox textbox, int index);
	void setElement(Label label, int index);

	/*Updateing Elements*/
	void updateGUI(sf::Vector2f mousePosition); // includes all update functions for GUI elements
	int updateButtons(sf::Vector2f mousePosition); // returns button index for pressed button
	void updateTextBoxes(sf::Vector2f mousePosition);
	void deselectTextboxes();
	void typeInTextBox(char letter);
	void updatePointers();

	/*Drawing to Window*/
	void drawGUI(sf::RenderWindow &window); // draw GUI elements to the window

private:
	/*Vectors that contain info on all GUI elements*/
	std::vector<Button> buttons;
	std::vector<TextBox> textboxes;
	std::vector<Label> labels;

	/*Mouse Information*/
	bool mouseHold;

};

