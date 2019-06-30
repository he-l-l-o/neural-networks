#include "image_conversion.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "textfield.h"
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
	short color_of_image_pixels[4][4][3];
	int type_lien;
};

int main()
{
	entry entry1;
	string file_location = "img/recommend_img.jpg";
	"The path to the file should not contain Cyrillic characters, but only Latin letters and numbers.\n";
	Image* load_image = new Image; //меню текстура
	if (load_image == NULL) {
		return -1;
	}
	load_image->loadFromFile(file_location);
	if (load_image->loadFromFile(file_location) == false) {
		return 1;
	}
	//создание главного окна приложения
	//графика основного интерфейса
	RenderWindow window(VideoMode(1200, 720), "NeyronBaseDataCreator", Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	Font font;
	font.loadFromFile("9041.ttf");
	//инициализация текстбокса
	textfield textfield;
	textfield.set_font(font);
	textfield.set_lenght(64);
	textfield.set_position(Vector2f(16, 629));

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

	Image button_arrow_up_image;
	button_arrow_up_image.loadFromFile("img/button_arrow_up.png");

	Image button_arrow_down_image;
	button_arrow_down_image.loadFromFile("img/button_arrow_down.png");

	Image button_arrow_left_image;
	button_arrow_left_image.loadFromFile("img/button_arrow_left.png");

	Image button_arrow_right_image;
	button_arrow_right_image.loadFromFile("img/button_arrow_right.png");

	Image button_load_image;
	button_load_image.loadFromFile("img/button_load_img.png");

	Texture main_texture;//главная текстура меню
	main_texture.loadFromImage(main_image);
	if (main_texture.loadFromImage(main_image) == false) {
		return 1;
	}

	Texture* load_image_texture = new Texture;//текстура загружаемого изображения
	load_image_texture->loadFromImage(*load_image);
	if (load_image_texture == NULL) {
		return -1;
	}
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

	Texture button_arrow_up_texture;
	button_arrow_up_texture.loadFromImage(button_arrow_up_image);

	Texture button_arrow_down_texture;
	button_arrow_down_texture.loadFromImage(button_arrow_down_image);

	Texture button_arrow_left_texture;
	button_arrow_left_texture.loadFromImage(button_arrow_left_image);

	Texture button_arrow_right_texture;
	button_arrow_right_texture.loadFromImage(button_arrow_right_image);

	Texture save_image_texture;

	Texture button_load_texture;
	button_load_texture.loadFromImage(button_load_image);

	Sprite main_sprite;
	main_sprite.setTexture(main_texture);
	main_sprite.setPosition(0, 0);

	Sprite* load_image_sprite = new Sprite;
	if (load_image_sprite == NULL) {
		return -1;
	}
	load_image_sprite->setTexture(*load_image_texture);
	load_image_sprite->setPosition(22, 20);

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

	Sprite button_arrow_up_sprite;
	button_arrow_up_sprite.setTexture(button_arrow_up_texture);
	button_arrow_up_sprite.setPosition(727, 441);

	Sprite button_arrow_down_sprite;
	button_arrow_down_sprite.setTexture(button_arrow_down_texture);
	button_arrow_down_sprite.setPosition(727, 517);

	Sprite button_arrow_left_sprite;
	button_arrow_left_sprite.setTexture(button_arrow_left_texture);
	button_arrow_left_sprite.setPosition(651, 517);

	Sprite button_arrow_right_sprite;
	button_arrow_right_sprite.setTexture(button_arrow_right_texture);
	button_arrow_right_sprite.setPosition(803, 517);

	Sprite button_load_sprite;
	button_load_sprite.setTexture(button_load_texture);
	button_load_sprite.setPosition(824, 625);

	Sprite check_image_sprite;
	Texture check_image_texture;

	FILE* binary_database;
	if (fopen_s(&binary_database, "data\\database.data", "ab+") != 0) {
		return 3;
	}

	//разметчик
	RectangleShape rectangle_pointer(Vector2f(4, 4));
	rectangle_pointer.setFillColor(Color::Red);
	rectangle_pointer.setPosition(22, 20);

	int size_x = load_image->getSize().x;
	int size_y = load_image->getSize().y;
	//вывод осуществялть через функции
	cout << "x = " << size_x << " y = " << size_y << endl;

	double ratio_x_y = (double)size_x / size_y;
	cout << "Ratio x - > y: " << ratio_x_y;

	int save_size_x = size_x;
	int save_size_y = size_y;

	scaling(size_x, size_y, save_size_x, save_size_y, ratio_x_y);
	//пустое окно
	RectangleShape rectangle_load_img(Vector2f(size_x, size_y));
	rectangle_load_img.setOutlineThickness(5);
	rectangle_load_img.setOutlineColor(sf::Color(250, 150, 100));
	rectangle_load_img.setPosition(17 + 5, 15 + 5);

	double ratio_load_img_menu = (double)save_size_x / size_x;
	cout << endl;
	cout << "Now size X " << size_x << " Now size Y " << size_y << endl;
	cout << "Save size X " << save_size_x << " Save size Y " << save_size_y << endl;
	cout << "Ratio loadIMG -> window " << ratio_load_img_menu << endl;
	cout << endl;
	///////////////////////////////////////////////
	Vector2f targetSize(size_x, size_y);

	load_image_sprite->setScale(
		targetSize.x / load_image_sprite->getGlobalBounds().width,
		targetSize.y / load_image_sprite->getGlobalBounds().height);

	Vector2f target_Size_save(198, 198);

	int location_marker_x;
	int location_marker_y;

	bool check_button_num = 0;

	bool check_button_null = 0;//проверка нажатия пустой кнопки
	bool check_button_vertical = 0;//проверка нажатися кнопки с вертикалью
	bool check_button_horizontal = 0;//проверка нажатия кнопки с горзонталью
	bool check_button_left_diagonal = 0;// проверка нажатия кнопки с левой диагональю
	bool check_button_right_diagonal = 0;//проверка нажатия кнопки с правой диагональю

	bool check_button_arrow_up = 0;//проверка нажатия кнопки перемещения вверх
	bool check_button_arrow_down = 0;//проверка нажатия кнопки перемещения вниз
	bool check_button_arrow_left = 0;//проверка нажатия кнопки перемещения влево
	bool check_button_arrow_right = 0;//проверка нажатия кнопки перемещение вправо

	bool check_button_load = 0;

	location_marker_x = (rectangle_pointer.getPosition().x - 22) * ratio_load_img_menu;
	location_marker_y = (rectangle_pointer.getPosition().y - 20) * ratio_load_img_menu;

	cout << "loaction x = " << location_marker_x << " location y = " << location_marker_y << endl;

	increase(*load_image_texture, save_image_sprite, location_marker_y, location_marker_x, target_Size_save);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			textfield.input(event, file_location);
			if (textfield.focus == 0) {
				if (((event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonPressed) &&
					(IntRect(824, 625, 67, 37).contains(Mouse::getPosition(window))))) {

					if (load_image->loadFromFile(file_location) == false) {
						textfield.focus = 1;
						load_image->loadFromFile(file_location);
					}
					else if (load_image->loadFromFile(file_location) == true) {

						button_load_sprite.setColor(Color(127, 127, 127));

						delete load_image_sprite;
						load_image_sprite = NULL;
						delete load_image_texture;
						load_image_texture = NULL;
						delete load_image;
						load_image = NULL;

						load_image = new Image;
						load_image_texture = new Texture;
						load_image_sprite = new Sprite;

						load_image->loadFromFile(file_location);
						load_image_texture->loadFromImage(*load_image);

						load_image_sprite->setTexture(*load_image_texture);
						load_image_sprite->setPosition(22, 20);

						size_x = load_image->getSize().x;
						size_y = load_image->getSize().y;

						ratio_x_y = (double)size_x / size_y;
						cout << "Ratio x - > y: " << ratio_x_y;

						save_size_x = size_x;
						save_size_y = size_y;

						scaling(size_x, size_y, save_size_x, save_size_y, ratio_x_y);

						rectangle_load_img.setSize(Vector2f(size_x, size_y));
						rectangle_load_img.setOutlineThickness(5);
						rectangle_load_img.setOutlineColor(sf::Color(250, 150, 100));
						rectangle_load_img.setPosition(17 + 5, 15 + 5);

						ratio_load_img_menu = (double)save_size_x / size_x;
						cout << endl;
						cout << "Now size X " << size_x << " Now size Y " << size_y << endl;
						cout << "Save size X " << save_size_x << " Save size Y " << save_size_y << endl;
						cout << "Ratio loadIMG -> window " << ratio_load_img_menu << endl;
						cout << endl;

						targetSize.x = size_x;
						targetSize.y = size_y;

						load_image_sprite->setScale(
							targetSize.x / load_image_sprite->getGlobalBounds().width,
							targetSize.y / load_image_sprite->getGlobalBounds().height);

						location_marker_x = (rectangle_pointer.getPosition().x - 22) * ratio_load_img_menu;
						location_marker_y = (rectangle_pointer.getPosition().y - 20) * ratio_load_img_menu;

						cout << "loaction x = " << location_marker_x << " location y = " << location_marker_y << endl;

						increase(*load_image_texture, save_image_sprite, location_marker_y, location_marker_x, target_Size_save);
					}
				}
				if ((event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonReleased) && (check_button_load == 1)) {
					button_load_sprite.setColor(Color(0, 0, 0));
					check_button_load = 0;
				}
				if (event.type == Event::Closed)
				{
					window.close();
				}

				////////////////UP
				if (((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Up)) || ((event.mouseButton.button == Mouse::Button::Left) && 
					(event.type == Event::MouseButtonPressed) && (IntRect(727, 441, 74, 74).contains(Mouse::getPosition(window)))))
				{
					//x < 620 x > 21 true else false
					button_arrow_up_sprite.setColor(Color(180, 180, 180, 255));

					rectangle_pointer.move(0, -1 / ratio_load_img_menu);
					location_marker_y = (rectangle_pointer.getPosition().y - 20) * ratio_load_img_menu;

					while (location_marker_y < 0)
					{
						rectangle_pointer.move(0, 1 / ratio_load_img_menu);
						location_marker_y = (rectangle_pointer.getPosition().y - 20) * ratio_load_img_menu;
					}
					increase(*load_image_texture, save_image_sprite, location_marker_y, location_marker_x, target_Size_save);
					cout << "x =  " << location_marker_x << " y = " << location_marker_y << endl;
					check_button_arrow_up = 1;
				}
				if ((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Up) || ((event.mouseButton.button == Mouse::Button::Left) && 
					(event.type == Event::MouseButtonReleased) && (check_button_arrow_up == 1)))
				{
					button_arrow_up_sprite.setColor(Color(255, 255, 255, 255));
					check_button_arrow_up = 0;
				}
				////////////////DOWN
				if (((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Down)) || (event.mouseButton.button == Mouse::Button::Left) && 
					(event.type == Event::MouseButtonPressed) && (IntRect(727, 517, 74, 74).contains(Mouse::getPosition(window))))
				{
					button_arrow_down_sprite.setColor(Color(180, 180, 180, 255));

					rectangle_pointer.move(0, 1 / ratio_load_img_menu);
					location_marker_y = (rectangle_pointer.getPosition().y - 20) * ratio_load_img_menu;
					while (location_marker_y > save_size_y - 4 * ratio_load_img_menu)
					{
						rectangle_pointer.move(0, -1 / ratio_load_img_menu);
						location_marker_y = (rectangle_pointer.getPosition().y - 20) * ratio_load_img_menu;
					}
					increase(*load_image_texture, save_image_sprite, location_marker_y, location_marker_x, target_Size_save);
					cout << "x =  " << location_marker_x << " y = " << location_marker_y << endl;
					check_button_arrow_down = 1;
				}
				if ((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Down) || (event.mouseButton.button == Mouse::Button::Left) && 
					(event.type == Event::MouseButtonReleased) && (check_button_arrow_down == 1))
				{
					button_arrow_down_sprite.setColor(Color(255, 255, 255, 255));
					check_button_arrow_down = 0;
				}
				/////////////////LEFT
				if (((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Left)) || (event.mouseButton.button == Mouse::Button::Left) && 
					(event.type == Event::MouseButtonPressed) && (IntRect(651, 517, 74, 74).contains(Mouse::getPosition(window))))
				{
					button_arrow_left_sprite.setColor(Color(180, 180, 180, 255));
					rectangle_pointer.move(-1 / ratio_load_img_menu, 0);
					location_marker_x = (rectangle_pointer.getPosition().x - 22) * ratio_load_img_menu;
					while (location_marker_x < 0)
					{
						rectangle_pointer.move(1 / ratio_load_img_menu, 0);
						location_marker_x = (rectangle_pointer.getPosition().y - 20) * ratio_load_img_menu;
					}
					location_marker_x = (rectangle_pointer.getPosition().x - 22) * ratio_load_img_menu;
					increase(*load_image_texture, save_image_sprite, location_marker_y, location_marker_x, target_Size_save);
					cout << "x =  " << location_marker_x << " y = " << location_marker_y << endl;
					//cout << "X = " << rectangle_pointer.getPosition().x << " Y = " << rectangle_pointer.getPosition().y << endl;
					check_button_arrow_left = 1;
				}
				if ((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Left) || (event.mouseButton.button == Mouse::Button::Left) &&
					(event.type == Event::MouseButtonReleased) && (check_button_arrow_left == 1))
				{
					button_arrow_left_sprite.setColor(Color(255, 255, 255, 255));
					check_button_arrow_left = 0;
				}
				/////////////////RIGHT
				if (((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Right)) || (event.mouseButton.button == Mouse::Button::Left) && 
					(event.type == Event::MouseButtonPressed) && (IntRect(803, 517, 74, 74).contains(Mouse::getPosition(window))))
				{
					button_arrow_right_sprite.setColor(Color(180, 180, 180, 255));
					rectangle_pointer.move(1 / ratio_load_img_menu, 0);
					location_marker_x = (rectangle_pointer.getPosition().x - 22) * ratio_load_img_menu;
					while (location_marker_x > save_size_x - 4 * ratio_load_img_menu)
					{
						rectangle_pointer.move(-1 / ratio_load_img_menu, 0);
						location_marker_x = (rectangle_pointer.getPosition().y - 20) * ratio_load_img_menu;
					}
					location_marker_x = (rectangle_pointer.getPosition().x - 22) * ratio_load_img_menu;
					increase(*load_image_texture, save_image_sprite, location_marker_y, location_marker_x, target_Size_save);
					cout << "x =  " << location_marker_x << " y = " << location_marker_y << endl;
					//cout << "X = " << rectangle_pointer.getPosition().x << " Y = " << rectangle_pointer.getPosition().y << endl;
					check_button_arrow_right = 1;
				}
				if ((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Right) || ((event.mouseButton.button == Mouse::Button::Left) &&
					(event.type == Event::MouseButtonReleased) && (check_button_arrow_right == 1)))
				{
					button_arrow_right_sprite.setColor(Color(255, 255, 255, 255));
					check_button_arrow_right = 0;
				}
				//TYPE NULL
				if (((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Num0)) ||
					(event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonPressed) &&
					(IntRect(654, 286, 212, 81).contains(Mouse::getPosition(window))))
				{
					button_type_0_sprite.setColor(Color(180, 180, 180, 255));
					check_button_null = 1;
				}
				if (((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Num0)) ||
					(event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonReleased) &&
					(check_button_null == 1))
				{
					Image check_image(save_image_sprite.getTexture()->copyToImage());
					get_color_array(entry1.color_of_image_pixels, *load_image, event, location_marker_x, location_marker_y);
					entry1.type_lien = 0;
					fwrite(&entry1, sizeof(entry1), 1, binary_database);
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							cout << entry1.color_of_image_pixels[j][i][0] << " ";
							cout << entry1.color_of_image_pixels[j][i][1] << " ";
							cout << entry1.color_of_image_pixels[j][i][2] << " ";
							cout << entry1.type_lien << endl;
						}
					}
					button_type_0_sprite.setColor(Color(255, 255, 255, 255));
					check_button_null = 0;
				}
				//TYPE ONE
				if (((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Num1)) ||
					(event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonPressed) &&
					(IntRect(892, 24, 212, 81).contains(Mouse::getPosition(window))))
				{
					button_type_1_sprite.setColor(Color(180, 180, 180, 255));
					check_button_vertical = 1;
				}
				if (((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Num1)) ||
					(event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonReleased) &&
					(check_button_vertical == 1))
				{
					Image check_image(save_image_sprite.getTexture()->copyToImage());
					get_color_array(entry1.color_of_image_pixels, *load_image, event, location_marker_x, location_marker_y);
					entry1.type_lien = 1;
					fwrite(&entry1, sizeof(entry1), 1, binary_database);
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							cout << entry1.color_of_image_pixels[j][i][0] << " ";
							cout << entry1.color_of_image_pixels[j][i][1] << " ";
							cout << entry1.color_of_image_pixels[j][i][2] << " ";
							cout << entry1.type_lien << endl;
						}
					}
					button_type_1_sprite.setColor(Color(255, 255, 255, 255));
					check_button_vertical = 0;
				}
				//TYPE TWO
				if (((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Num2)) ||
					(event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonPressed) &&
					(IntRect(892, 109, 212, 81).contains(Mouse::getPosition(window))))
				{
					button_type_2_sprite.setColor(Color(180, 180, 180, 255));
					check_button_horizontal = 1;
				}
				if (((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Num2)) ||
					(event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonReleased)
					&& (check_button_horizontal == 1))
				{
					Image check_image(save_image_sprite.getTexture()->copyToImage());
					get_color_array(entry1.color_of_image_pixels, *load_image, event, location_marker_x, location_marker_y);
					entry1.type_lien = 2;
					fwrite(&entry1, sizeof(entry1), 1, binary_database);
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							cout << entry1.color_of_image_pixels[j][i][0] << " ";
							cout << entry1.color_of_image_pixels[j][i][1] << " ";
							cout << entry1.color_of_image_pixels[j][i][2] << " ";
							cout << entry1.type_lien << endl;
						}
					}
					button_type_2_sprite.setColor(Color(255, 255, 255, 255));
					check_button_horizontal = 0;
				}
				//TYPE 3
				if (((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Num3)) ||
					(event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonPressed)
					&& (IntRect(892, 194, 212, 81).contains(Mouse::getPosition(window))))
				{
					button_type_3_sprite.setColor(Color(180, 180, 180, 255));
					check_button_left_diagonal = 1;
				}
				if (((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Num3)) ||
					(event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonReleased)
					&& (check_button_left_diagonal == 1))
				{
					Image check_image(save_image_sprite.getTexture()->copyToImage());
					get_color_array(entry1.color_of_image_pixels, *load_image, event, location_marker_x, location_marker_y);
					entry1.type_lien = 3;
					fwrite(&entry1, sizeof(entry1), 1, binary_database);
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							cout << entry1.color_of_image_pixels[j][i][0] << " ";
							cout << entry1.type_lien << endl;
						}
					}
					button_type_3_sprite.setColor(Color(255, 255, 255, 255));
					check_button_left_diagonal = 0;
				}
				//TYPE 4
				if (((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Num4)) || (event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonPressed) && (IntRect(892, 284, 212, 81).contains(Mouse::getPosition(window))))
				{
					button_type_4_sprite.setColor(Color(180, 180, 180, 255));
					check_button_right_diagonal = 1;
				}
				if (((event.type == Event::KeyReleased) && (event.key.code == Keyboard::Num4)) ||
					(event.mouseButton.button == Mouse::Button::Left) && (event.type == Event::MouseButtonReleased) &&
					(check_button_right_diagonal == 1))
				{
					Image check_image(save_image_sprite.getTexture()->copyToImage());
					get_color_array(entry1.color_of_image_pixels, *load_image, event, location_marker_x, location_marker_y);
					entry1.type_lien = 4;
					fwrite(&entry1, sizeof(entry1), 1, binary_database);
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							cout << entry1.color_of_image_pixels[j][i][0] << " ";
							cout << entry1.color_of_image_pixels[j][i][1] << " ";
							cout << entry1.color_of_image_pixels[j][i][2] << " ";
							cout << entry1.type_lien << endl;
						}
					}
					button_type_4_sprite.setColor(Color(255, 255, 255, 255));
					check_button_right_diagonal = 0;
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		window.clear();

		window.draw(main_sprite);
		window.draw(rectangle_load_img);
		window.draw(*load_image_sprite);
		window.draw(rectangle_pointer);
		window.draw(save_image_sprite);
		window.draw(button_load_sprite);
		window.draw(button_type_0_sprite);
		window.draw(button_type_1_sprite);
		window.draw(button_type_2_sprite);
		window.draw(button_type_3_sprite);
		window.draw(button_type_4_sprite);
		window.draw(button_arrow_up_sprite);
		window.draw(button_arrow_down_sprite);
		window.draw(button_arrow_left_sprite);
		window.draw(button_arrow_right_sprite);
		textfield.render(window);
		window.display();
	}

	delete load_image_sprite;
	load_image_sprite = NULL;
	delete load_image_texture;
	load_image_texture = NULL;
	delete load_image;
	load_image = NULL;

	fclose(binary_database);
}