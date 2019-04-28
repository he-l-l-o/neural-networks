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
	Image LoadpapImage;//кнопка загрузки
	LoadpapImage.loadFromFile("images/Loadpap.png");
	Image SavepapImage;//кнопка сохранения
	SavepapImage.loadFromFile("images/Save.png");

	Texture MenuImageTexture;//создаем текстуру меню
	MenuImageTexture.loadFromImage(MenuImage);
	Texture LoadpapImageTexture;//создаем текстуру кнопки загрузки
	LoadpapImageTexture.loadFromImage(LoadpapImage);
	Texture SavepapImageTexture;//создаем текстуру кнопки сохранения
	SavepapImageTexture.loadFromImage(SavepapImage);
	
	Sprite MenuImageSprite; //создаем спрайт меню
	MenuImageSprite.setTexture(MenuImageTexture);
	MenuImageSprite.setPosition(0, 0);
	Sprite LoadpapImageSprite; //создаем спрайт кнопки загрузки
	LoadpapImageSprite.setTexture(LoadpapImageTexture);
	LoadpapImageSprite.setPosition(422, 532);
	Sprite SavepapImageSprite; //создаем спрайт кнопки сохранения
	SavepapImageSprite.setTexture(SavepapImageTexture);
	SavepapImageSprite.setPosition(952, 532);

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
		
		window.draw(LoadpapImageSprite);//рисуем иконку папки

		window.draw(SavepapImageSprite);//рисуем иконку сохранения

		window.display();
	}
	return 0;
}