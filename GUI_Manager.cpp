#include "GUI_Manager.h"

/*Construcotrs*/
GUI_Manager::GUI_Manager() {
	mouseHold = false;
}

/*Adding GUI Elements*/
void GUI_Manager::addButton(Button button) {
	buttons.push_back(button);
	// update pointer to font and image
	updatePointers();
}
void GUI_Manager::addTextBox(TextBox textbox) {
	textboxes.push_back(textbox);
	// update pointer to font and image
	updatePointers();
}
void GUI_Manager::addLabel(Label label) {
	labels.push_back(label);
	// update pointer to font and image
	updatePointers();
}

/*Get Elements*/
Button GUI_Manager::getButton(int index) {
	return buttons.at(index);
}
TextBox GUI_Manager::getTextbox(int index) {
	return textboxes.at(index);
}
Label GUI_Manager::getLabel(int index) {
	return labels.at(index);
}

/*Set Elements*/
void GUI_Manager::setElement(Button button, int index) {
	buttons.at(index) = button;
	buttons.at(index).setFont(buttons.at(index).getFontPath());
}
void GUI_Manager::setElement(TextBox textbox, int index) {
	textboxes.at(index) = textbox;
	textboxes.at(index).setFont(buttons.at(index).getFontPath());
}
void GUI_Manager::setElement(Label label, int index) {
	labels.at(index) = label;
	labels.at(index).setFont(buttons.at(index).getFontPath());
}

/*Updates*/
void GUI_Manager::updateGUI(sf::Vector2f mousePosition) {
	updateButtons(mousePosition);
	updateTextBoxes(mousePosition);
}
int GUI_Manager::updateButtons(sf::Vector2f mousePosition) {
	for (int i = buttons.size() - 1; i >= 0; i--) {
		int buttonState = buttons.at(i).update(mousePosition, mouseHold);
		if (buttonState == 1 || buttonState == 2) {
			for (int x = buttons.size() - 1; x >= 0; x--) { buttons.at(x).shape.setFillColor(buttons.at(x).getIdleColor()); } // make all idle color
			for (int x = buttons.size() - 1; x >= 0; x--) { // update top selected button
				buttonState = buttons.at(i).update(mousePosition, mouseHold);
				if (buttonState == 2) return i;
				if (buttonState == 1) break;
			} 
			break;
		}
	}
}
void GUI_Manager::updateTextBoxes(sf::Vector2f mousePosition) {
	for (int i = textboxes.size() - 1; i >= 0; i--) {
		if (textboxes.at(i).update(mousePosition, mouseHold)) {
			textboxes.at(i).setSelected(true);
		}
	}
}
void GUI_Manager::deselectTextboxes() {
	for (int i = textboxes.size() - 1; i >= 0; i--) {
		textboxes.at(i).setSelected(false);
	}
}
void GUI_Manager::typeInTextBox(char letter) {
	for (int i = textboxes.size() - 1; i >= 0; i--) {
		if (textboxes.at(i).isSelected()) {
			if (letter == 8) {
				if (textboxes.at(i).text.getString() == "") break;
				std::string string = textboxes.at(i).text.getString().toAnsiString();
				string.pop_back();
				textboxes.at(i).text.setString(string);
			}
			else if (textboxes.at(i).text.getGlobalBounds().width >= textboxes.at(i).shape.getSize().x - textboxes.at(i).shape.getOutlineThickness() * 6){
				break;
			}
			else {
				textboxes.at(i).text.setString(textboxes.at(i).text.getString() + letter);
			}
			break;
		}
	}
}
void GUI_Manager::updatePointers() {
	for (unsigned i = 0; i != labels.size(); ++i) {
		labels.at(i).setFont(labels.at(i).getFontPath());
	}
	for (unsigned i = 0; i != buttons.size(); ++i) {
		buttons.at(i).setFont(buttons.at(i).getFontPath());
	}
	for (unsigned i = 0; i != textboxes.size(); ++i) {
		textboxes.at(i).setFont(textboxes.at(i).getFontPath());
	}
}

/*Mouse Information*/
void GUI_Manager::setMouseHold(bool state) {
	mouseHold = state;
}
bool GUI_Manager::getMouseHold() {
	return mouseHold;
}

/*Draw GUI Elements*/
void GUI_Manager::drawGUI(sf::RenderWindow & window) {
	// buttons
	for (unsigned i = 0; i != buttons.size(); ++i) {
		window.draw(buttons.at(i).shape);
		window.draw(buttons.at(i).text);
	}
	for (unsigned i = 0; i != textboxes.size(); ++i) {
		window.draw(textboxes.at(i).shape);
		window.draw(textboxes.at(i).text);
		window.draw(textboxes.at(i).cursor);
	}
	for (int i = 0; i != labels.size(); ++i) {
		window.draw(labels.at(i).shape);
		window.draw(labels.at(i).text);
	}
}