#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

int main()
{
	string file_location;
	getline(cin, file_location);
	//создание главного окна приложения
	RenderWindow window(VideoMode(1200, 720), "NeyronBaseDataCreator");
	//графика основного интерфейса
	Image main_image;
	main_image.loadFromFile("img/menu.png");

	Texture main_texture;
	main_texture.loadFromImage(main_image);

	Sprite main_sprite;
	main_sprite.setTexture(main_texture);
	main_sprite.setPosition(0, 0);
	//load picture
	Image load_image;
	load_image.loadFromFile(file_location);

	Texture load_image_texture;
	load_image_texture.loadFromImage(load_image);

	Sprite load_image_sprite;
	load_image_sprite.setTexture(load_image_texture);
	load_image_sprite.setPosition(22, 20);

	Sprite save_image_sprite;
	//text string
	//объявление шрифта
	//Font font;
	//font.loadFromFile("9041.ttf");
	//объявление окна-разметчика
	RectangleShape rectangle_razmer(Vector2f(8,8));
	rectangle_razmer.setFillColor(Color::Red);
	rectangle_razmer.setOutlineThickness(10);
	rectangle_razmer.setOutlineColor(Color(250, 150, 100));
	rectangle_razmer.setPosition(22, 20);
	//new .cpp and .h
	/////////////////////////////////////
	int size_of_x = load_image.getSize().x;
	int size_of_y = load_image.getSize().y;
	cout << "x = " << size_of_x << " y = " << size_of_y << endl;

	double relationship_x_y = (double)size_of_x / size_of_y;
	cout << "Relationshio x -> y: " << relationship_x_y;

	int save_size_of_x = size_of_x;
	int save_size_of_y = size_of_y;

	if (size_of_x > size_of_y) {
		while (size_of_x > 608) {
			size_of_x = size_of_x - 1;
		}
		size_of_y = size_of_x / relationship_x_y;
	}
	else if (size_of_y > size_of_x) {
		while (size_of_y > 600) {
			size_of_y = size_of_y - 1;
		}
		if ((save_size_of_x > 608) && (save_size_of_y > 600)) {
			size_of_x = size_of_x * relationship_x_y;
		}
	}
	cout << endl;
	cout << size_of_x << " " << size_of_y << endl;
	cout << save_size_of_x << " " << save_size_of_y;
	cout << endl;
	///////////////////////////////////////////////
	Vector2f targetSize(608, 600);
	load_image_sprite.setScale(
		targetSize.x / load_image_sprite.getGlobalBounds().width,
		targetSize.y / load_image_sprite.getGlobalBounds().height);
	
	int location_marker_x;
	int location_marker_y;

	location_marker_x = rectangle_razmer.getPosition().x;
	location_marker_y = rectangle_razmer.getPosition().y;
	
	RectangleShape rect_save;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.KeyPressed)
			{
				if ((event.key.code == Keyboard::Right) || (event.key.code == Keyboard::Left))
				{
					location_marker_x = rectangle_razmer.getPosition().x;
				}
				if ((event.key.code == Keyboard::Up) || (event.key.code == Keyboard::Down))
				{
					location_marker_y = rectangle_razmer.getPosition().y;
				}
			}
			if (event.KeyReleased)
			{
				if ((event.key.code == Keyboard::Up) || (event.key.code == Keyboard::Down) || (event.key.code == Keyboard::Right) || (event.key.code == Keyboard::Left))
				{
					cout << "x = " << location_marker_x << "  " << "y = " << location_marker_y << endl;
				}
				if (event.key.code == Keyboard::Enter)
				{
					IntRect form;
					form = (IntRect)rectangle_razmer.getGlobalBounds();
					//form.left -= 22;
					//form.top -= 20;
					save_image_sprite.setTexture(load_image_texture);
					save_image_sprite.setTextureRect(form);
					save_image_sprite.setPosition(600, 300);
				}
			}
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			rectangle_razmer.move(-1, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			rectangle_razmer.move(1, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			rectangle_razmer.move(0, -1);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			rectangle_razmer.move(0, 1);
		}
		
		///////new cppp

		window.clear();
		window.draw(main_sprite);
		window.draw(load_image_sprite);
		window.draw(rectangle_razmer);
		window.draw(save_image_sprite);
		window.display();
	}

	return 0;
}
