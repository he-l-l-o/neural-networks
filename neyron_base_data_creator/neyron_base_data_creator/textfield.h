#ifndef TXTFIELD_H
#define TXTFIELD_H

#include <string>
#include <SFML/Graphics.hpp>

class textfield {
public:
	textfield();

	void set_position(sf::Vector2f vector);
private:
	sf::Text text;
	sf::RectangleShape text_box;
	int size;
	int lenght;

	sf::Vector2f position;
};

#endif