void ratio_func(double &size_x, double &size_y, double &ratio) {
	if (size_x > size_y) {
		while (size_x > 475) {
			size_x = size_x - 1;
		}
		size_y = size_x / ratio;
	}
	else if (size_y > size_x) {
		while (size_y > 475) {
			size_y = size_y - 1;
		}
		size_x = size_y * ratio;
	}
}