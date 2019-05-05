#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
	// Создаем главное окно приложения
	RenderWindow window(VideoMode(1000, 600), "NeuralNetworks");

	Image menu_image;//создаем меню
	menu_image.loadFromFile("images/menu.png");
	Image load_pap_image;//кнопка загрузки
	load_pap_image.loadFromFile("images/Loadpap.png");
	Image save_pap_image;//кнопка сохранения
	save_pap_image.loadFromFile("images/Save.png");
	Image load_image;//создаем картинку
	load_image.loadFromFile("images/LoadImage.jpg");
	double size_x = load_image.getSize().x, size_y = load_image.getSize().y;//Считываем размеры картинки
	double ratio = size_x / size_y; // отношение x к y

	int save_size_x = size_x, save_size_y = size_y;//сохраняем кол-во пикселей

	////////////////////////СЖАТИЕ ИЗОБРАЖЕНИЯ ДО РАЗМЕРОВ ОКНА////////////////
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
	///////////////////////////////////////////////////////////////////////////

	////////////////////////ТРЕХМЕРНЫЙ ДИНАМИЧЕСКИЙ МАССИВ/////////////////////
	//1)Инициализация
	int ***arr_image = new int **[save_size_y];
	for (int i = 0; i < save_size_y; i++)
	{
		arr_image[i] = new int *[save_size_x];
		for (int j = 0; j < save_size_x; j++)
			arr_image[i][j] = new int[3];
	}
	//2)Заполнение
	for (int i = 0; i < save_size_y; i++)
	{
		for (int j = 0; j < save_size_x; j++)
		{
			arr_image[i][j][0] = load_image.getPixel(j, i).r; //Красная часть цветовой модели
			arr_image[i][j][1] = load_image.getPixel(j, i).g; //Зеленая часть цветовой модели
			arr_image[i][j][2] = load_image.getPixel(j, i).b; //Синяя часть цветовой модели
		}
	}
	///////////////////////////////////////////////////////////////////////////

	Texture menu_image_texture;//создаем текстуру меню
	menu_image_texture.loadFromImage(menu_image);
	Texture load_pap_image_texture;//создаем текстуру кнопки загрузки
	load_pap_image_texture.loadFromImage(load_pap_image);
	Texture save_pap_image_texture;//создаем текстуру кнопки сохранения
	save_pap_image_texture.loadFromImage(save_pap_image);
	Texture load_image_texture;//создаем текстуру загруженной картинки
	load_image_texture.loadFromImage(load_image);

	Image save_image;//Создание нового изображения
	save_image.create(save_size_x, save_size_y, Color(255, 255, 100, 100));

	//Создание изображения из массива пискелей
	for (int i = 0; i < save_size_y; i++) {
		for (int j = 0; j < save_size_x; j++) {
			save_image.setPixel(j, i, Color(arr_image[i][j][0], arr_image[i][j][1], arr_image[i][j][2], 255));
		}
	}

	Texture save_image_texture;//Создание текстуры под новое изображение
	save_image_texture.loadFromImage(save_image);

	Sprite menu_image_sprite; //создаем спрайт меню
	menu_image_sprite.setTexture(menu_image_texture);
	menu_image_sprite.setPosition(0, 0);
	Sprite load_pap_image_sprite; //создаем спрайт кнопки загрузки
	load_pap_image_sprite.setTexture(load_pap_image_texture);
	load_pap_image_sprite.setPosition(422, 532);
	Sprite save_pap_image_sprite; //создаем спрайт кнопки сохранения
	save_pap_image_sprite.setTexture(save_pap_image_texture);
	save_pap_image_sprite.setPosition(952, 532);
	Sprite load_image_sprite; //создаем спрайт загруженной картинки
	load_image_sprite.setTexture(load_image_texture);
	load_image_sprite.setPosition(23, 23);
	Sprite save_image_sprite;
	save_image_sprite.setTexture(save_image_texture);
	save_image_sprite.setPosition(503, 23);

	Vector2f target_size(size_x, size_y); //целевой размеp
	load_image_sprite.setScale(
		target_size.x / load_image_sprite.getGlobalBounds().width,
		target_size.y / load_image_sprite.getGlobalBounds().height);
	Vector2f target_size1(size_x, size_y); //целевой размеp
	save_image_sprite.setScale(
		target_size1.x / save_image_sprite.getGlobalBounds().width,
		target_size1.y / save_image_sprite.getGlobalBounds().height);

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
				if (IntRect(422, 532, 27, 27).contains(Mouse::getPosition(window))) {
					load_pap_image_sprite.setColor(Color::Blue);
				}
				if (IntRect(952, 532, 26, 26).contains(Mouse::getPosition(window))) {
					save_pap_image_sprite.setColor(Color::Blue);
				}
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
		window.draw(menu_image_sprite);//рисуем меню

		window.draw(load_pap_image_sprite);//рисуем иконку папки

		window.draw(save_pap_image_sprite);//рисуем иконку сохранения

		window.draw(load_image_sprite);//рисуем Загруженную картинку

		window.draw(save_image_sprite);//рисуем полученную картинку

		save_image.saveToFile("images/SaveImage.jpg");//Сохранение картинки

		window.display();
	}

	//Освобождение памяти
	for (int i = 0; i < save_size_y; i++) {
		for (int j = 0; j < save_size_x; j++) {
			delete[] arr_image[i][j];
		}
		delete[] arr_image[i];
	}
	delete[] arr_image;

	return 0;
}