#include "textfield.h"
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

textfield::textfield() {
	textbox.setFillColor(sf::Color::White);
	textbox.setOutlineThickness(3);

	text.setFillColor(sf::Color::Black);

	focus = false;
	render_placeholder = false;

	length = 0;
}
void textfield::set_position(sf::Vector2f vector) {
	textbox.setPosition(vector);
	text.setPosition(vector + sf::Vector2f(5, 5));
}
void textfield::set_font(sf::Font& font) {
	text.setFont(font);
	text.setCharacterSize(24);//������������� ������ �������
	textbox.setSize(sf::Vector2f((text.getCharacterSize() * (size / 2 + 1)) + 10, text.getCharacterSize() + 10));
}

void textfield::render(sf::RenderWindow& window) {
	window.draw(textbox);
	window.draw(text);
}

void textfield::set_lenght(int string_lenght) {
	size = string_lenght;
	textbox.setSize(sf::Vector2f((text.getCharacterSize() * (size / 2 + 1)) + 10, text.getCharacterSize() + 10));
}

void textfield::set_focus(bool active) {
	focus = active;
	if (focus) {
		textbox.setOutlineColor(sf::Color::Green);
	}
	else {
		textbox.setOutlineColor(sf::Color::White);
	}

	if (render_placeholder && active) {
		render_placeholder = false;
		text.setString("");
		text.setFillColor(sf::Color::Black);
	}
}

void textfield::input(sf::Event event, std::string& file_location) {
	if (event.type == sf::Event::MouseButtonReleased) {
		sf::Vector2f position(event.mouseButton.x, event.mouseButton.y);
		if (textbox.getGlobalBounds().contains(position)) {
			set_focus(true);
		}
		else {
			set_focus(false);
		}
	}

	if (event.type == sf::Event::TextEntered && focus) {
		sf::String string = text.getString();
		if (event.text.unicode == 8) {
			if (string.getSize() > 0) {
				length--;
				string = string.substring(0, string.getSize() - 1);
			}
		}
		else if (event.text.unicode == 24) {
			set_focus(false);
		}
		else {
			sf::String sf_string = "";
			sf_string += event.text.unicode;
			string += sf_string.toAnsiString();
		}

		if (string.getSize() == size) {
			return;
		}
		text.setString(string);
		length++;
		file_location = string;
		std::cout << file_location << std::endl;
	}
}
