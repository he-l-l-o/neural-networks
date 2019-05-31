#pragma once
#include <SFML/Graphics.hpp>
void scaling(int &size_x, int &size_y, int save_size_x, int save_size_y, double ratio_x_y);
void get_color_array(short color_of_image_pixels[4][4], sf::Image load_image, sf::Event event, int location_marker_x, int location_marker_y);