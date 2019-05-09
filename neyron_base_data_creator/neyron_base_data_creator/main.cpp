#include "image_conversion.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;
using namespace sf;
/*
	[x][y][1] = R;
	[x][y][2] = G;
	[x][y][3] = B;

	0 .. x = size_x;
	0 .. y = size_y;
*/
struct entry {
	short color_of_image_pixels[8][8][3];
	int type_lien;
};
int main()
{
	struct entry entry1;
	string file_location;
	cout << "Please enter the location of the loaded picture.\n WARNING!!!\n The path to the file should not contain Cyrillic characters, but only Latin letters and numbers.\n";
	getline(cin, file_location);
	//создание главного окна приложения
	//графика основного интерфейса
	RenderWindow window(VideoMode(1200, 720), "NeyronBaseDataCreator");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	Image main_image;//меню image
	main_image.loadFromFile("img/menu.png");
	Image load_image;//меню текстура
	load_image.loadFromFile(file_location);
	Image save_image;// меню спрайт

	Texture main_texture;
	main_texture.loadFromImage(main_image);
	Texture load_image_texture;
	load_image_texture.loadFromImage(load_image);
	Texture save_image_texture;

	Sprite main_sprite;
	main_sprite.setTexture(main_texture);
	main_sprite.setPosition(0, 0);
	Sprite load_image_sprite;
	load_image_sprite.setTexture(load_image_texture);
	load_image_sprite.setPosition(22, 20);
	Sprite save_image_sprite;//вырезанный кусочек изображения

	RectangleShape rectangle_razmer(Vector2f(8, 8));
	rectangle_razmer.setFillColor(Color::Red);
	rectangle_razmer.setPosition(22, 20);

	int size_of_x = load_image.getSize().x;
	int size_of_y = load_image.getSize().y;
	cout << "x = " << size_of_x << " y = " << size_of_y << endl;

	double ratio_x_y = (double)size_of_x / size_of_y;
	cout << "Relationship x -> y: " << ratio_x_y;
	//масштабирование относительно изображения относительно окна
	int save_size_of_x = size_of_x;
	int save_size_of_y = size_of_y;
	if (size_of_x > size_of_y) {
		while (size_of_x > 608) {
			size_of_x = size_of_x - 1;
		}
		size_of_y = size_of_x / ratio_x_y;
	}
	else if (size_of_y > size_of_x) {
		while (size_of_y > 600) {
			size_of_y = size_of_y - 1;
		}
		if ((save_size_of_x > 608) && (save_size_of_y > 600)) {
			size_of_x = size_of_x * ratio_x_y;
		}
	}
	cout << endl;
	cout << "Now size X " << size_of_x << " Now size Y " << size_of_y << endl;
	cout << "Save size X " << save_size_of_x << " Save size Y " << save_size_of_y;
	cout << endl;
	///////////////////////////////////////////////
	Vector2f targetSize(608, 600);
	load_image_sprite.setScale(
		targetSize.x / load_image_sprite.getGlobalBounds().width,
		targetSize.y / load_image_sprite.getGlobalBounds().height);

	Vector2f target_Size_save(198, 198);

	int location_marker_x;
	int location_marker_y;

	location_marker_x = rectangle_razmer.getPosition().x;
	location_marker_y = rectangle_razmer.getPosition().y;
	cout << "loaction x = " << location_marker_x << " location y = " << location_marker_y;
	RectangleShape rect_save;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.KeyPressed) {
				if ((event.key.code == Keyboard::Right) || (event.key.code == Keyboard::Left)) {
					location_marker_x = rectangle_razmer.getPosition().x;
				}
				if ((event.key.code == Keyboard::Up) || (event.key.code == Keyboard::Down)) {
					location_marker_y = rectangle_razmer.getPosition().y;
				}
			}
			if (event.KeyReleased)
			{
				if ((event.key.code == Keyboard::Up) || (event.key.code == Keyboard::Down) || (event.key.code == Keyboard::Right) || (event.key.code == Keyboard::Left))
				{
					cout << "x = " << location_marker_x << "  " << "y = " << location_marker_y << endl;
				}
				if (event.key.code == Keyboard::Enter)
				{
					IntRect form;
					form = (IntRect)rectangle_razmer.getGlobalBounds();
					//form.left -= 22;
					//form.top -= 20;
					save_image_sprite.setTexture(load_image_texture);
					save_image_sprite.setTextureRect(form);
					save_image_sprite.setScale(
						target_Size_save.x / save_image_sprite.getGlobalBounds().width,
						target_Size_save.y / save_image_sprite.getGlobalBounds().height);
					save_image_sprite.setPosition(649, 21);
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			rectangle_razmer.move(-1, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			rectangle_razmer.move(1, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			rectangle_razmer.move(0, -1);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			rectangle_razmer.move(0, 1);
		}

		///////new cppp

		window.clear();
		window.draw(main_sprite);
		window.draw(load_image_sprite);
		window.draw(rectangle_razmer);
		window.draw(save_image_sprite);
		window.display();
	}
}