#ifndef TXTFIELD_H
#define TXTFIELD_H

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
class textfield {
public:
	textfield();

	void set_position(sf::Vector2f vector);//задание позиции
	void set_font(sf::Font& font);//задание шрифта
	void set_lenght(int string_lenght);//задание длины текстбокса
	void input(sf::Event event, std::string& file_location);//фокусировка на текстбоксе и запись в строковую переменную
	void render(sf::RenderWindow& window);
	//void set_placeholder(std::string string);


private:
	sf::Text text;
	sf::RectangleShape textbox;
	int size;
	int length;
	bool focus;
	bool render_placeholder;

	void set_focus(bool active);

	sf::Vector2f position;
};

#endif