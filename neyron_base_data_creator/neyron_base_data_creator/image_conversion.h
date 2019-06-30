#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
void scaling(int& size_x, int& size_y, int save_size_x, int save_size_y, double ratio_x_y);
void get_color_array(short color_of_image_pixels[4][4], sf::Image load_image, sf::Event event, int location_marker_x, int location_marker_y, int type_button_color);
int check_load_img(sf::Image load_image, std::string& file_location);
void increase(sf::Texture& load_image_texture, sf::Sprite& save_image_sprite, int location_marker_y, int location_marker_x, sf::Vector2f target_Size_save, int type_button_color);