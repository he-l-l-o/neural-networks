#ifndef TXTFIELD_H
#define TXTFIELD_H

#include <string>
#include <SFML/Graphics.hpp>

class textfield {
public:
	textfield();

	void set_position(sf::Vector2f vector);//������� �������
	void set_font(sf::Font& font);//������� ������
	void set_lenght(int string_lenght);//������� ����� ����������
	void input(sf::Event event);//����������� �� ������
	void render(sf::RenderWindow& window);


private:
	sf::Text text;
	sf::RectangleShape textbox;
	int size;
	int lenght;
	bool focus;
	bool render_placeholder;

	void set_focus(bool active);

	sf::Vector2f position;
};

#endif