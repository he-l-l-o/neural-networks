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
//0 - red, 1 - green, 2 - blue
//переделать 
void get_color_array(short color_of_image_pixels[4][4], sf::Image load_image, sf::Event event, int location_marker_x, int location_marker_y, int type_color) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {

			switch (type_color) {
			case 0:
				std::cout << "RED" << std::endl;
				color_of_image_pixels[j][i] = load_image.getPixel(location_marker_x + j, location_marker_y + i).r;
				break;
			case 1:
				std::cout << "GREEN" << std::endl;
				color_of_image_pixels[j][i] = load_image.getPixel(location_marker_x + j, location_marker_y + i).g;
				break;
			case 2:
				std::cout << "BLUE" << std::endl;
				color_of_image_pixels[j][i] = load_image.getPixel(location_marker_x + j, location_marker_y + i).b;
				break;
			default: exit(4);
			}
		}
	}
}

int check_load_img(sf::Image load_image, std::string & file_location) {
	while (load_image.loadFromFile(file_location) == false) {
		std::getline(std::cin, file_location);
		load_image.loadFromFile(file_location);
	}
	if (load_image.loadFromFile(file_location) == true) {
		return 1;
	}
}

void increase(sf::Texture & load_image_texture, sf::Sprite & save_image_sprite, int location_marker_y, int location_marker_x, sf::Vector2f target_Size_save, int type_button_color) {
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

	switch (type_button_color) {
	case 0: 
		save_image_sprite.setColor(sf::Color(255, 0, 0)); 
		break;
	case 1: 
		save_image_sprite.setColor(sf::Color(0, 255, 0)); 
		break;
	case 2: 
		save_image_sprite.setColor(sf::Color(0, 0, 255));
		break;
	default: exit(4);
	}

}