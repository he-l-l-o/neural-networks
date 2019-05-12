﻿#include "image_conversion.h"
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
} entry1;
/*
void check_file(string file_location, Image load_image) {
	if (load_image.loadFromFile(file_location) == false) {
		cout << "file not location. PLease, try input again" << endl;
		getline(cin, file_location);
		check_file(file_location, load_image);
	}
}*/
int main()
{
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
//	check_file(file_location, load_image);

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
	
	FILE* binary_database;
	fopen_s(&binary_database, "data\\database.data", "ab+");
	
	//разметчик
	RectangleShape rectangle_pointer(Vector2f(8, 8));
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
	bool counter = 0;
	location_marker_x = (rectangle_pointer.getPosition().x - 22) * ratio_load_img_menu;
	location_marker_y = (rectangle_pointer.getPosition().y - 20) * ratio_load_img_menu;
	cout << "loaction x = " << location_marker_x << " location y = " << location_marker_y << endl;
	
	RectangleShape rect_save;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			bool check_button = 0;
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.KeyPressed) {
				if ((event.key.code == Keyboard::Right) || (event.key.code == Keyboard::Left)) {
					location_marker_x = (rectangle_pointer.getPosition().x - 22) * ratio_load_img_menu;
					check_button = 1;
				}
				if ((event.key.code == Keyboard::Up) || (event.key.code == Keyboard::Down)) {
					location_marker_y = (rectangle_pointer.getPosition().y - 20) * ratio_load_img_menu;
					check_button = 1;
				}
				if ((event.key.code == Keyboard::Num0) || (event.key.code == Keyboard::Num1) || (event.key.code == Keyboard::Num2) || (event.key.code == Keyboard::Num3) || (event.key.code == Keyboard::Num4)) {
					check_button = 1;
				}
			}
			if (event.KeyReleased && check_button)
			{
				if ((event.key.code == Keyboard::Up) || (event.key.code == Keyboard::Down) || (event.key.code == Keyboard::Right) || (event.key.code == Keyboard::Left))
				{
					cout << "x = " << location_marker_x << "  " << "y = " << location_marker_y << endl;
					check_button = 0;
				}
				if ((event.key.code == Keyboard::Up) || (event.key.code == Keyboard::Down) || (event.key.code == Keyboard::Right) || (event.key.code == Keyboard::Left))
				{
					IntRect form;
					form.height = 8;
					form.width = 8;
					form.top = location_marker_y;
					form.left = location_marker_x;

					save_image_sprite.setTexture(load_image_texture);
					save_image_sprite.setTextureRect(form);
					save_image_sprite.setPosition(649, 21);

					save_image_sprite.setScale(
						target_Size_save.x / 8,
						target_Size_save.y / 8);
					check_button = 0;
				}
				if ((event.key.code == Keyboard::Num0) || (event.key.code == Keyboard::Num1) || (event.key.code == Keyboard::Num2) || (event.key.code == Keyboard::Num3) || (event.key.code == Keyboard::Num4))
				{ 
					Image mirror_image(save_image_sprite.getTexture()->copyToImage());
					get_color_array(entry1.color_of_image_pixels, load_image, event, location_marker_x, location_marker_y);
					entry1.type_lien = event.key.code - 26;
					fwrite(&entry1, sizeof(entry1), 1, binary_database);

					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							cout << entry1.color_of_image_pixels[j][i][0] << " ";
							cout << entry1.color_of_image_pixels[j][i][1] << " ";
							cout << entry1.color_of_image_pixels[j][i][2] << " ";
							cout << entry1.type_lien << endl;
						}
					}
					cout << endl;
					mirror_image.flipHorizontally();
					cout<< endl << "FLIP HORIZ" << endl;
					if (entry1.type_lien == 3) {
								get_color_array(entry1.color_of_image_pixels, mirror_image, event, location_marker_x, location_marker_y);
								entry1.type_lien = 4;
								fwrite(&entry1, sizeof(entry1), 1, binary_database);

								cout << "SMENA 3 NA 4" << endl;
								for (int i = 0; i < 8; i++) {
									for (int j = 0; j < 8; j++) {
										cout << entry1.color_of_image_pixels[j][i][0] << " ";
										cout << entry1.color_of_image_pixels[j][i][1] << " ";
										cout << entry1.color_of_image_pixels[j][i][2] << "  ";
										cout << entry1.type_lien << endl;
									}
								}
								cout << endl;
					} else if (entry1.type_lien == 4) {
								get_color_array(entry1.color_of_image_pixels, mirror_image, event, location_marker_x, location_marker_y);
								entry1.type_lien = 3;
								fwrite(&entry1, sizeof(entry1), 1, binary_database);
								cout << "SMENA 4 NA 3" << endl;
								for (int i = 0; i < 8; i++) {
									for (int j = 0; j < 8; j++) {
										cout << entry1.color_of_image_pixels[j][i][0] << " ";
										cout << entry1.color_of_image_pixels[j][i][1] << " ";
										cout << entry1.color_of_image_pixels[j][i][2] << "  ";
										cout << entry1.type_lien << endl;
									}
								}
								cout << endl;
					} else {
						get_color_array(entry1.color_of_image_pixels, mirror_image, event, location_marker_x, location_marker_y);
						entry1.type_lien = event.key.code - 26;
						fwrite(&entry1, sizeof(entry1), 1, binary_database);
						for (int i = 0; i < 8; i++) {
							for (int j = 0; j < 8; j++) {
								cout << entry1.color_of_image_pixels[j][i][0] << " ";
								cout << entry1.color_of_image_pixels[j][i][1] << " ";
								cout << entry1.color_of_image_pixels[j][i][2] << "  ";
								cout << entry1.type_lien << endl;
							}
						}
						cout << endl;
					}

					mirror_image.flipVertically();
					cout << endl <<"FLIP VERT" << endl;
					if (entry1.type_lien == 3) {
						get_color_array(entry1.color_of_image_pixels, mirror_image, event, location_marker_x, location_marker_y);
						entry1.type_lien = 4;
						fwrite(&entry1, sizeof(entry1), 1, binary_database);
						cout << "SMENA 3 NA 4" << endl;

						for (int i = 0; i < 8; i++) {
							for (int j = 0; j < 8; j++) {
								cout << entry1.color_of_image_pixels[j][i][0] << " ";
								cout << entry1.color_of_image_pixels[j][i][1] << " ";
								cout << entry1.color_of_image_pixels[j][i][2] << "  ";
								cout << entry1.type_lien << endl;
							}
						}
						cout << endl;
					}
					else if (entry1.type_lien == 4) {
						get_color_array(entry1.color_of_image_pixels, mirror_image, event, location_marker_x, location_marker_y);
						entry1.type_lien = 3;
						fwrite(&entry1, sizeof(entry1), 1, binary_database);
						cout << "SMENA 4 NA 3" << endl;
						
						for (int i = 0; i < 8; i++) {
							for (int j = 0; j < 8; j++) {
								cout << entry1.color_of_image_pixels[j][i][0] << " ";
								cout << entry1.color_of_image_pixels[j][i][1] << " ";
								cout << entry1.color_of_image_pixels[j][i][2] << "  ";
								cout << entry1.type_lien << endl << endl;
							}
						}
						cout << endl;
					}
					else {
						get_color_array(entry1.color_of_image_pixels, mirror_image, event, location_marker_x, location_marker_y);
						entry1.type_lien = event.key.code - 26;
						fwrite(&entry1, sizeof(entry1), 1, binary_database);

						for (int i = 0; i < 8; i++) {
							for (int j = 0; j < 8; j++) {
								cout << entry1.color_of_image_pixels[j][i][0] << " ";
								cout << entry1.color_of_image_pixels[j][i][1] << " ";
								cout << entry1.color_of_image_pixels[j][i][2] << "  ";
								cout << entry1.type_lien << endl;
							}
						}
						cout << endl;
					}
					check_button = 0;
				}
				
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			if ((rectangle_pointer.getPosition().x < 620) && (rectangle_pointer.getPosition().x > 21)) {
				rectangle_pointer.move(-0.1, 0);
			}
			else {
				rectangle_pointer.move(10, 0);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			if ((rectangle_pointer.getPosition().x < 620) && (rectangle_pointer.getPosition().x > 21)) {
				rectangle_pointer.move(0.1, 0);
			}
			else {
				rectangle_pointer.move(-10, 0);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			if ((rectangle_pointer.getPosition().y < 619) && (rectangle_pointer.getPosition().y > 19)) {
				rectangle_pointer.move(0, -0.1);
			}
			else {
				rectangle_pointer.move(0, 10);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			if ((rectangle_pointer.getPosition().y < 619) && (rectangle_pointer.getPosition().y > 19)) {
				rectangle_pointer.move(0, 0.1);
			}
			else {
				rectangle_pointer.move(0, -10);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		window.clear();
		window.draw(main_sprite);
		window.draw(load_image_sprite);
		window.draw(rectangle_pointer);
		window.draw(save_image_sprite);
		window.display();
	}
	fclose(binary_database);
}