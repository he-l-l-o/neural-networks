#include "textfield.h"
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

textfield::textfield() {
	text_box.setFillColor(sf::Color::White);
	text_box.setOutlineThickness(3);
}
void textfield::set_position(sf::Vector2f vector) {
	text_box.setPosition(vector);
}