#include <SFML/Graphics.hpp>
#include "image_conversion.h"

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
