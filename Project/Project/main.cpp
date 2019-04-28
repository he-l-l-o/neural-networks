#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
	// Создаем главное окно приложения
	RenderWindow window(VideoMode(1000, 600), "NeuralNetworks");

	Image MenuImage;//создаем меню
	MenuImage.loadFromFile("images/menu.png");

	Texture MenuImageTexture;//создаем текстуру меню
	MenuImageTexture.loadFromImage(MenuImage);

	Sprite MenuImageSprite; //создаем спрайт меню
	MenuImageSprite.setTexture(MenuImageTexture);
	MenuImageSprite.setPosition(0, 0);

	// Главный цикл приложения
	while (window.isOpen())
	{
		// Обрабатываем события в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Кроме обычного способа наше окно будет закрываться по нажатию на Escape
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
				window.close();
		}

		// Очистка
		window.clear();
		// Тут будут вызываться функции обновления и отрисовки объектов
		// Отрисовка
		window.draw(MenuImageSprite);//рисуем меню
		
		window.display();
	}
	return 0;
}