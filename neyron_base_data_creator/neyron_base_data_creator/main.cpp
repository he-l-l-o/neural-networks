#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
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

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}

	return 0;
}
