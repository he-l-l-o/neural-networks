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
	Image LoadImage;//создаем картинку
	LoadImage.loadFromFile("images/LoadImage.jpg");
	double size_of_x = LoadImage.getSize().x, size_of_y = LoadImage.getSize().y;//Считываем размеры картинки
	double ratio = size_of_x / size_of_y; // отношение x к y
	
	int save_size_of_x = size_of_x, save_size_of_y = size_of_y;//сохраняем кол-во пикселей

	if (size_of_x > size_of_y) {
		while (size_of_x > 475) {
			size_of_x = size_of_x - 1;
		}
		size_of_y = size_of_x / ratio;
	}
	else if (size_of_y > size_of_x) {
		while (size_of_y > 475) {
			size_of_y = size_of_y - 1;
		}
		size_of_x = size_of_y * ratio;
	}

	Texture MenuImageTexture;//создаем текстуру меню
	MenuImageTexture.loadFromImage(MenuImage);
	Texture LoadpapImageTexture;//создаем текстуру кнопки загрузки
	LoadpapImageTexture.loadFromImage(LoadpapImage);
	Texture SavepapImageTexture;//создаем текстуру кнопки сохранения
	SavepapImageTexture.loadFromImage(SavepapImage);
	Texture LoadImageTexture;//создаем текстуру загруженной картинки
	LoadImageTexture.loadFromImage(LoadImage);
	
	Sprite MenuImageSprite; //создаем спрайт меню
	MenuImageSprite.setTexture(MenuImageTexture);
	MenuImageSprite.setPosition(0, 0);
	Sprite LoadpapImageSprite; //создаем спрайт кнопки загрузки
	LoadpapImageSprite.setTexture(LoadpapImageTexture);
	LoadpapImageSprite.setPosition(422, 532);
	Sprite SavepapImageSprite; //создаем спрайт кнопки сохранения
	SavepapImageSprite.setTexture(SavepapImageTexture);
	SavepapImageSprite.setPosition(952, 532);
	Sprite LoadImageSprite; //создаем спрайт загруженной картинки
	LoadImageSprite.setTexture(LoadImageTexture);
	LoadImageSprite.setPosition(23, 23);

	Vector2f targetSize(size_of_x, size_of_y); //целевой размеp
	LoadImageSprite.setScale(
		targetSize.x / LoadImageSprite.getGlobalBounds().width,
		targetSize.y / LoadImageSprite.getGlobalBounds().height);

	// Главный цикл приложения
	while (window.isOpen())
	{
		// Обрабатываем события в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Кроме обычного способа наше окно будет закрываться по нажатию на Escape
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (IntRect(422, 532, 27, 27).contains(Mouse::getPosition(window))) { LoadpapImageSprite.setColor(Color::Blue); }
				if (IntRect(952, 532, 26, 26).contains(Mouse::getPosition(window))) { SavepapImageSprite.setColor(Color::Blue); }

				if (event.mouseButton.button == sf::Mouse::Left) {
					if (event.mouseButton.x >= 422 && event.mouseButton.x <= 449 && event.mouseButton.y >= 532 && event.mouseButton.y <= 558) {
						cout << "the right button was pressed on Loadpap" << endl;
						cout << "mouse x: " << event.mouseButton.x << endl;
						cout << "mouse y: " << event.mouseButton.y << endl;
					}
				}
				if (event.mouseButton.button == sf::Mouse::Left) {
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

		window.draw(LoadImageSprite);//рисуем Загруженную картинку

		window.display();
	}
	return 0;
}