#include <SFML/Graphics.hpp>
#include "image_conversion.h"
#include <iostream>
#include <string>

void scaling(int& size_x, int& size_y, int save_size_x, int save_size_y, double ratio_x_y)
{
	if (size_x > size_y) {
		while (size_x > 608) {
			size_x = size_x - 1;
		}
		size_y = size_x / ratio_x_y;
	}
	else if (size_y > size_x) {
		while (size_y > 600) {
			size_y = size_y - 1;
		}
		if ((save_size_x > 608) && (save_size_y > 600)) {
			size_x = size_x * ratio_x_y;
		}
	}
}

void get_color_array(short color_of_image_pixels[4][4][3], sf::Image load_image, sf::Event event, int location_marker_x, int location_marker_y) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			color_of_image_pixels[j][i][0] = load_image.getPixel(location_marker_x + j, location_marker_y + i).r;
			color_of_image_pixels[j][i][1] = load_image.getPixel(location_marker_x + j, location_marker_y + i).g;
			color_of_image_pixels[j][i][2] = load_image.getPixel(location_marker_x + j, location_marker_y + i).b;
		}
	}
}

int check_load_img(sf::Image load_image, std::string & file_location) {
	while (load_image.loadFromFile(file_location) == false) {
		std::cout << "NOPE! This file is empty in folder. Plesae, input correct road. Good luck!\n";
		std::getline(std::cin, file_location);
		load_image.loadFromFile(file_location);
	}
	if (load_image.loadFromFile(file_location) == true) {
		return 1;
	}
}

void increase(sf::Texture &load_image_texture, sf::Sprite &save_image_sprite, int location_marker_y, int location_marker_x, sf::Vector2f target_Size_save) {
	sf::IntRect form;
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

void move_pointer(sf::RectangleShape &rectangle_pointer) {
	if ((rectangle_pointer.getPosition().x < 620) && (rectangle_pointer.getPosition().x > 21))
	{
		rectangle_pointer.move(-0.1, 0);
	}
	else
	{
		rectangle_pointer.move(10, 0);
	}
}
