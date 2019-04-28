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

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (IntRect(422, 532, 27, 27).contains(Mouse::getPosition(window))) { LoadpapImageSprite.setColor(Color::Blue); }
				if (IntRect(952, 532, 26, 26).contains(Mouse::getPosition(window))) { SavepapImageSprite.setColor(Color::Blue); }

				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (event.mouseButton.x >= 422 && event.mouseButton.x <= 449 && event.mouseButton.y >= 532 && event.mouseButton.y <= 558) {
						cout << "the right button was pressed on Loadpap" << endl;
						cout << "mouse x: " << event.mouseButton.x << endl;
						cout << "mouse y: " << event.mouseButton.y << endl;
					}
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (event.mouseButton.x >= 952 && event.mouseButton.x <= 978 && event.mouseButton.y >= 532 && event.mouseButton.y <= 558) {
						cout << "the right button was pressed on Save" << endl;
						cout << "mouse x: " << event.mouseButton.x << endl;
						cout << "mouse y: " << event.mouseButton.y << endl;
					}
				}
			}
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