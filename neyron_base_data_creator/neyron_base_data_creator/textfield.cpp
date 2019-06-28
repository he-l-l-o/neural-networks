#include "textfield.h"
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

textfield::textfield() {
	text_box.setFillColor(sf::Color::White);
	text_box.setOutlineThickness(3);
	
	text.setFillColor(sf::Color::Black);
}
void textfield::set_position(sf::Vector2f vector) {
	text_box.setPosition(vector);
	text.setPosition(vector + sf::Vector2f(5, 5));
}
void textfield::set_font(sf::Font& font) {
	text.setFont(font);
	text.setCharacterSize(24);//устанавливаем размер символа
	text_box.setSize(sf::Vector2f((text.getCharacterSize() * (size / 2 + 1)) + 10, text.getCharacterSize() + 10));
}

void textfield::render(sf::RenderWindow& window) {
	window.draw(text_box);
	window.draw(text);
}
