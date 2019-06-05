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
struct entry
{
	short color_of_image_pixels[4][4];
	int type_lien;
} entry1;

int main()
{
	string file_location;
	cout << "Please enter the location of the loaded picture.\n WARNING!!!\n"
		"The path to the file should not contain Cyrillic characters, but only Latin letters and numbers.\n";
	getline(cin, file_location);
	Image load_image; //меню текстура
	load_image.loadFromFile(file_location);
	//создание главного окна приложения
	//графика основного интерфейса
	RenderWindow window(VideoMode(1200, 720), "NeyronBaseDataCreator");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	Image main_image; //меню image
	main_image.loadFromFile("img/menu.png");
	Image save_image; // меню спрайт
	//////КНОПЕКИ//////////
	Image button_type_0_image;
	button_type_0_image.loadFromFile("img/button_type_0.png");
	Image button_type_1_image;
	button_type_1_image.loadFromFile("img/button_type_1.png");
	Image button_type_2_image;
	button_type_2_image.loadFromFile("img/button_type_2.png");
	Image button_type_3_image;
	button_type_3_image.loadFromFile("img/button_type_3.png");
	Image button_type_4_image;
	button_type_4_image.loadFromFile("img/button_type_4.png");

	Texture main_texture;//главная текстура меню
	main_texture.loadFromImage(main_image);

	Texture load_image_texture;//текстура загружаемого изображения
	load_image_texture.loadFromImage(load_image);

	Texture button_type_0_texture;//текстура кнопки 0
	button_type_0_texture.loadFromImage(button_type_0_image);
	Texture button_type_1_texture;//текстура кнопки 1
	button_type_1_texture.loadFromImage(button_type_1_image);
	Texture button_type_2_texture;//текстура кнопки 2
	button_type_2_texture.loadFromImage(button_type_2_image);
	Texture button_type_3_texture;//текстура кнопки 3
	button_type_3_texture.loadFromImage(button_type_3_image);
	Texture button_type_4_texture;//текстура кнопки 4
	button_type_4_texture.loadFromImage(button_type_4_image);

	Texture save_image_texture;

	Sprite main_sprite;
	main_sprite.setTexture(main_texture);
	main_sprite.setPosition(0, 0);
	Sprite load_image_sprite;
	load_image_sprite.setTexture(load_image_texture);
	load_image_sprite.setPosition(22, 20);

	Sprite save_image_sprite; //вырезанный кусочек изображения

	Sprite button_type_0_sprite;//текстура кнопки 0
	button_type_0_sprite.setTexture(button_type_0_texture);
	button_type_0_sprite.setPosition(654, 286);
	Sprite button_type_1_sprite;//текстура кнопки 1
	button_type_1_sprite.setTexture(button_type_1_texture);
	button_type_1_sprite.setPosition(892, 19);
	Sprite button_type_2_sprite;//текстура кнопки 2
	button_type_2_sprite.setTexture(button_type_2_texture);
	button_type_2_sprite.setPosition(892, 109);

	Sprite button_type_3_sprite;//текстура кнопки 3
	button_type_3_sprite.setTexture(button_type_3_texture);
	button_type_3_sprite.setPosition(892, 194);

	Sprite button_type_4_sprite;//текстура кнопки 3
	button_type_4_sprite.setTexture(button_type_4_texture);
	button_type_4_sprite.setPosition(892, 284);


	Sprite check_image_sprite;
	Texture check_image_texture;

	FILE* binary_database;
	fopen_s(&binary_database, "data\\database.data", "ab+");

	//разметчик
	RectangleShape rectangle_pointer(Vector2f(4, 4));
	rectangle_pointer.setFillColor(Color::Red);
	rectangle_pointer.setPosition(22, 20);

	int size_x = load_image.getSize().x;
	int size_y = load_image.getSize().y;
	//вывод осуществялть через функции
	cout << "x = " << size_x << " y = " << size_y << endl;

	double ratio_x_y = (double)size_x / size_y;
	cout << "Ratio x - > y: " << ratio_x_y;

	int save_size_x = size_x;
	int save_size_y = size_y;

	scaling(size_x, size_y, save_size_x, save_size_y, ratio_x_y);

	double ratio_load_img_menu = (double)save_size_x / size_x;
	cout << endl;
	cout << "Now size X " << size_x << " Now size Y " << size_y << endl;
	cout << "Save size X " << save_size_x << " Save size Y " << save_size_y << endl;
	cout << "Ratio loadIMG -> window " << ratio_load_img_menu << endl;
	cout << endl;
	///////////////////////////////////////////////
	Vector2f targetSize(size_x, size_y);

	load_image_sprite.setScale(
		targetSize.x / load_image_sprite.getGlobalBounds().width,
		targetSize.y / load_image_sprite.getGlobalBounds().height);

	Vector2f target_Size_save(198, 198);

	int location_marker_x;
	int location_marker_y;

	bool check_button_num = 0;

	bool check_button_null = 0;//проверка нажатия пустой кнопки
	bool check_button_vertical = 0;//проверка нажатися кнопки с вертикалью
	bool check_button_horizontal = 0;//проверка нажатия кнопки с горзонталью
	bool check_button_left_diagonal = 0;// проверка нажатия кнопки с левой диагональю
	bool check_button_right_diagonal = 0;//проверка нажатия кнопки с правой диагональю

	location_marker_x = (rectangle_pointer.getPosition().x - 22) * ratio_load_img_menu;
	location_marker_y = (rectangle_pointer.getPosition().y - 20) * ratio_load_img_menu;

	cout << "loaction x = " << location_marker_x << " location y = " << location_marker_y << endl;

	RectangleShape rect_save;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			/////////////////////////////////
			if ((event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonPressed) && (IntRect(654, 286, 212, 81).contains(Mouse::getPosition(window))))
			{
				button_type_0_sprite.setColor(Color(180, 180, 180, 255));
				check_button_null = 1;
			}
			if ((event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonReleased) && (check_button_null == 1))
			{
				button_type_0_sprite.setColor(Color(255, 255, 255, 255));
				check_button_null = 0;
			}
			/////////////////
			if ((event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonPressed) && (IntRect(892, 24, 212, 81).contains(Mouse::getPosition(window))))
			{
				button_type_1_sprite.setColor(Color(180, 180, 180, 255));
				check_button_vertical = 1;
			}
			if ((event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonReleased) && (check_button_vertical == 1))
			{
				button_type_1_sprite.setColor(Color(255, 255, 255, 255));
				check_button_vertical = 0;
			}
			////////////////////////
			if ((event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonPressed) && (IntRect(892, 109, 212, 81).contains(Mouse::getPosition(window))))
			{
				button_type_2_sprite.setColor(Color(180, 180, 180, 255));
				check_button_horizontal = 1;
			}
			if ((event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonReleased) && (check_button_horizontal == 1))
			{
				button_type_2_sprite.setColor(Color(255, 255, 255, 255));
				check_button_horizontal = 0;
			}
			///////////////////////
			if ((event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonPressed) && (IntRect(892, 194, 212, 81).contains(Mouse::getPosition(window))))
			{
				button_type_3_sprite.setColor(Color(180, 180, 180, 255));
				check_button_left_diagonal = 1;
			}
			if ((event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonReleased) && (check_button_left_diagonal == 1))
			{
				button_type_3_sprite.setColor(Color(255, 255, 255, 255));
				check_button_left_diagonal = 0;
			}
		
			//////////////////////
			if ((event.KeyPressed) && (event.key.code == Keyboard::Right) || (event.key.code == Keyboard::Left))
			{
				location_marker_x = (rectangle_pointer.getPosition().x - 22) * ratio_load_img_menu;
			}
			if ((event.KeyPressed) && (event.key.code == Keyboard::Up) || (event.key.code == Keyboard::Down))
			{
				location_marker_y = (rectangle_pointer.getPosition().y - 20) * ratio_load_img_menu;
			}
			//////////////////////
			if ((event.KeyReleased) && (((event.key.code == Keyboard::Up) || (event.key.code == Keyboard::Down) || (event.key.code == Keyboard::Right) || (event.key.code == Keyboard::Left))))
			{

				cout << "x = " << location_marker_x << "  " << "y = " << location_marker_y << endl;
				IntRect form;
				form.height = 4;
				form.width = 4;
				form.top = location_marker_y;
				form.left = location_marker_x;

				save_image_sprite.setTexture(load_image_texture);
				save_image_sprite.setTextureRect(form);
				save_image_sprite.setPosition(649, 21);

				save_image_sprite.setScale(
					target_Size_save.x / 4,
					target_Size_save.y / 4);
			}
			if ((event.KeyReleased) && ((event.key.code == Keyboard::Num0) || (event.key.code == Keyboard::Num1) || (event.key.code == Keyboard::Num2) || (event.key.code == Keyboard::Num3) || (event.key.code == Keyboard::Num4)))
			{

				Image check_image(save_image_sprite.getTexture()->copyToImage());
				get_color_array(entry1.color_of_image_pixels, load_image, event, location_marker_x, location_marker_y);
				entry1.type_lien = event.key.code - 26;
				fwrite(&entry1, sizeof(entry1), 1, binary_database);
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						cout << entry1.color_of_image_pixels[j][i] << " ";
						cout << entry1.type_lien << endl;
					}
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			if ((rectangle_pointer.getPosition().x < 620) && (rectangle_pointer.getPosition().x > 21))
			{
				rectangle_pointer.move(-0.1, 0);
			}
			else
			{
				rectangle_pointer.move(10, 0);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if ((rectangle_pointer.getPosition().x < 620) && (rectangle_pointer.getPosition().x > 21))
			{
				rectangle_pointer.move(0.1, 0);
			}
			else
			{
				rectangle_pointer.move(-10, 0);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if ((rectangle_pointer.getPosition().y < 619) && (rectangle_pointer.getPosition().y > 19))
			{
				rectangle_pointer.move(0, -0.1);
			}
			else
			{
				rectangle_pointer.move(0, 10);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			if ((rectangle_pointer.getPosition().y < 619) && (rectangle_pointer.getPosition().y > 19))
			{
				rectangle_pointer.move(0, 0.1);
			}
			else
			{
				rectangle_pointer.move(0, -10);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		window.clear();

		window.draw(main_sprite);
		window.draw(load_image_sprite);
		window.draw(rectangle_pointer);
		window.draw(save_image_sprite);
		window.draw(button_type_0_sprite);
		window.draw(button_type_1_sprite);
		window.draw(button_type_2_sprite);
		window.draw(button_type_3_sprite);
		window.draw(button_type_4_sprite);
		window.display();
	}
	fclose(binary_database);
}