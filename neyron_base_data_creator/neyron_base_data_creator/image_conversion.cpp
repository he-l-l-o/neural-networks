#include <SFML/Graphics.hpp>
#include "image_conversion.h"
#include <iostream>

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

void get_color_array(short color_of_image_pixels[4][4], sf::Image load_image, sf::Event event, int location_marker_x, int location_marker_y) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			color_of_image_pixels[j][i] = load_image.getPixel(location_marker_x + j, location_marker_y + i).r;
		//	color_of_image_pixels[j][i][1] = load_image.getPixel(location_marker_x + j, location_marker_y + i).g;
		//	color_of_image_pixels[j][i][2] = load_image.getPixel(location_marker_x + j, location_marker_y + i).b;
		}
	}
}

