#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "ratio.h"
#include "../..//neyron_base_data_creator/neyron_base_data_creator/textfield.h"

using namespace sf;
using namespace std;

int main()
{
	setlocale(0, "");

	// Создаем главное окно приложения
	RenderWindow window(VideoMode(1000, 600), "NeuralNetworks");

	string stroka_load; //переменная для ввода текста пути загрузки
	string stroka_save; //переменная для ввода текста пути сохранения

	Font font;                                //инициализация шрифта
	font.loadFromFile("Times New Roman.ttf"); //передаем файл с шрифтом в font

	Text text_load(L"", font, 20);   //инициализация текста с путем для загрузки
	text_load.setStyle(Text::Bold);  //делаем текст загрузки жирным
	text_load.setPosition(27, 532);  //местоположение текста загрузки
	Text text_save(L"", font, 20);   //инициализация текста с путем для сохранения
	text_save.setStyle(Text::Bold);  //делаем текст загрузки жирным
	text_save.setPosition(557, 532); //местоположение текста загрузки

	textfield textfiel_load;
	textfiel_load.set_font(font);
	textfiel_load.set_lenght(33);
	textfiel_load.set_position(sf::Vector2f(22, 532));

	textfield textfiel_save;
	textfiel_save.set_font(font);
	textfiel_save.set_lenght(32);
	textfiel_save.set_position(sf::Vector2f(527, 532));

	Image menu_image;                                   //инициализация изображения меню
	menu_image.loadFromFile("images/menu.png");         //передаем изображение в menu_image
	Image load_pap_image;                               //инициализация изображения кнопки загрузки
	load_pap_image.loadFromFile("images/Load_pap.png"); //передаем изображение в load_pap_image
	Image save_pap_image;                               //инициализация изображения кнопки сохранения
	save_pap_image.loadFromFile("images/Save.png");     //передаем изображение в save_pap_image
	Image load_image;                                   //инициализация загруженного изображения
	Image save_image;                                   //инициализация сохраненного изображения

	Texture menu_image_texture;                           //инциализация текстуры для menu_image
	menu_image_texture.loadFromImage(menu_image);         //передача menu_image в menu_image_texture
	Texture load_pap_image_texture;                       //инциализация текстуры для load_pap_image
	load_pap_image_texture.loadFromImage(load_pap_image); //передача load_pap_image в load_pap_image_texture
	Texture save_pap_image_texture;                       //инциализация текстуры для save_pap_image
	save_pap_image_texture.loadFromImage(save_pap_image); //передача save_pap_image в save_pap_image_texture
	Texture load_image_texture;                           //создаем текстуру загруженной картинки
	Texture save_image_texture;                           //Создание текстуры под новое изображение

	Sprite menu_image_sprite; //инициализация спрайта меню
	menu_image_sprite.setTexture(menu_image_texture);
	menu_image_sprite.setPosition(0, 0);
	Sprite load_pap_image_sprite; //инициализация спрайта кнопки загрузки
	load_pap_image_sprite.setTexture(load_pap_image_texture);
	load_pap_image_sprite.setPosition(450, 532);
	Sprite save_pap_image_sprite; //инициализация спрайта кнопки сохранения
	save_pap_image_sprite.setTexture(save_pap_image_texture);
	save_pap_image_sprite.setPosition(952, 532);
	Sprite load_image_sprite; //инициализация спрайта загруженной картинки
	Sprite save_image_sprite; //инициализация спрайта обратботанной картинки

	//создаем рамку для изображений
	RectangleShape rectangle_load;
	rectangle_load.setFillColor(Color::Green);
	rectangle_load.setOutlineColor(sf::Color::Red);
	rectangle_load.setOutlineThickness(2);

	RectangleShape rectangle_save;
	rectangle_save.setFillColor(Color::Green);
	rectangle_save.setOutlineThickness(2);
	rectangle_save.setOutlineColor(sf::Color::Red);

	// Главный цикл приложения
	while (window.isOpen())
	{
		// Обрабатываем события в цикле
		Event event;
		while (window.pollEvent(event))
		{
			textfiel_load.input(event, stroka_load);
			textfiel_save.input(event, stroka_save);

			load_pap_image_sprite.setColor(Color::White);
			save_pap_image_sprite.setColor(Color::White);

			if (IntRect(450, 532, 27, 27).contains(Mouse::getPosition(window)))
			{
				load_pap_image_sprite.setColor(Color(180, 180, 180, 255));
			}
			if (IntRect(952, 532, 26, 26).contains(Mouse::getPosition(window)))
			{
				save_pap_image_sprite.setColor(Color(180, 180, 180, 255));
			}

			// Кроме обычного способа наше окно будет закрываться по нажатию на Escape
			if (event.type == Event::Closed ||
				(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
			{
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (IntRect(450, 532, 27, 27).contains(Mouse::getPosition(window)))
				{
					load_pap_image_sprite.setColor(Color(180, 180, 180, 255));
				}
				if (IntRect(952, 532, 26, 26).contains(Mouse::getPosition(window)))
				{
					save_pap_image_sprite.setColor(Color(180, 180, 180, 255));
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (event.mouseButton.x >= 450 && event.mouseButton.x <= 476 &&
						event.mouseButton.y >= 532 && event.mouseButton.y <= 558)
					{
						//getline(cin, stroka_load); //консольный ввод

						load_image.loadFromFile(stroka_load); //взятие изображения по адресу(строки)

						double size_x = load_image.getSize().x; //Считываем размеры картинки
						double size_y = load_image.getSize().y;
						double ratio = size_x / size_y; // отношение x к y

						int save_size_x = size_x, save_size_y = size_y; //сохраняем кол-во пикселей

						////////////////////////СЖАТИЕ ИЗОБРАЖЕНИЯ ДО РАЗМЕРОВ ОКНА////////////////
						ratio_func(size_x, size_y, ratio); //расчет нового разрешения загруженного изображения
						///////////////////////////////////////////////////////////////////////////

						////////////////////////ТРЕХМЕРНЫЙ ДИНАМИЧЕСКИЙ МАССИВ/////////////////////
						//1)Инициализация
						int*** arr_image = new int** [save_size_y];
						for (int i = 0; i < save_size_y; i++)
						{
							arr_image[i] = new int* [save_size_x];
							for (int j = 0; j < save_size_x; j++)
							{
								arr_image[i][j] = new int[3];
							}
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

						////////////////////////ТРЕХМЕРНЫЙ ДИНАМИЧЕСКИЙ МАССИВ С РЕЗУЛЬТАТАМИ/////////////////////
						//1)Инициализация
						int*** arr_image_processing = new int** [save_size_y];
						for (int i = 0; i < save_size_y; i++)
						{
							arr_image_processing[i] = new int* [save_size_x];
							for (int j = 0; j < save_size_x; j++)
							{
								arr_image_processing[i][j] = new int[3];
							}
						}
						//2)Заполнение
						for (int i = 0; i < save_size_y; i++)
						{
							for (int j = 0; j < save_size_x; j++)
							{
								arr_image_processing[i][j][0] = 255; //Красная часть цветовой модели
								arr_image_processing[i][j][1] = 255; //Зеленая часть цветовой модели
								arr_image_processing[i][j][2] = 255; //Синяя часть цветовой модели
							}
						}
						///////////////////////////////////////////////////////////////////////////

						load_image_texture.loadFromImage(load_image); //передача load_image в load_image_texture

						save_image.create(save_size_x, save_size_y, Color(0, 0, 0, 100)); //создание нового изображения

						//Создание изображения из массива пискелей
						for (int i = 0; i < save_size_y; i++)
						{
							for (int j = 0; j < save_size_x; j++)
							{
								save_image.setPixel(j, i, Color(arr_image[i][j][0], arr_image[i][j][1], arr_image[i][j][2], 255));
							}
						}

						save_image_texture.loadFromImage(save_image); //передача save_image в save_image_texture

						load_image_sprite.setTexture(load_image_texture);                      //передача load_image_texture в load_image_texture
						load_image_sprite.setPosition(259 - (size_x / 2), 259 - (size_y / 2)); //установка позиции load_image_sprite

						save_image_sprite.setTexture(save_image_texture);                      //передача save_image_texture в save_image_sprite
						save_image_sprite.setPosition(762 - (size_x / 2), 259 - (size_y / 2)); //установка позиции save_image_sprite

						Vector2f target_size(size_x, size_y); //целевой размеp загружаемого изображения
						load_image_sprite.setScale(
							target_size.x / load_image_sprite.getGlobalBounds().width,
							target_size.y / load_image_sprite.getGlobalBounds().height);
						Vector2f target_size1(size_x, size_y); //целевой размеp обработанного изображения
						save_image_sprite.setScale(
							target_size1.x / save_image_sprite.getGlobalBounds().width,
							target_size1.y / save_image_sprite.getGlobalBounds().height);

						rectangle_load.setSize(sf::Vector2f(size_x, size_y));
						rectangle_save.setSize(sf::Vector2f(size_x, size_y));
						rectangle_load.setPosition(259 - (size_x / 2), 259 - (size_y / 2));
						rectangle_save.setPosition(762 - (size_x / 2), 259 - (size_y / 2));

						//Освобождение памяти
						for (int i = 0; i < save_size_y; i++)
						{
							for (int j = 0; j < save_size_x; j++)
							{
								delete[] arr_image[i][j];
							}
							delete[] arr_image[i];
						}
						delete[] arr_image;
					}
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (event.mouseButton.x >= 952 && event.mouseButton.x <= 978 &&
						event.mouseButton.y >= 532 && event.mouseButton.y <= 558)
					{
						//getline(cin, stroka_save); //консольный ввод

						save_image.saveToFile(stroka_save /*"images/SaveImage.jpg"*/); //Сохранение картинки
					}
				}
			}
		}

		// Очистка
		window.clear();
		// Тут будут вызываться функции обновления и отрисовки объектов
		// Отрисовка
		window.draw(menu_image_sprite); //рисуем меню

		window.draw(load_pap_image_sprite); //рисуем иконку папки

		window.draw(save_pap_image_sprite); //рисуем иконку сохранения

		window.draw(rectangle_load); //рисуем рамку изображения

		window.draw(rectangle_save);

		window.draw(load_image_sprite); //рисуем Загруженную картинку

		window.draw(save_image_sprite); //рисуем полученную картинку

		text_load.setString(stroka_load);
		window.draw(text_load); //рисуем текст для загрузки картинки

		text_save.setString(stroka_save);
		window.draw(text_save); //рисуем текст для сохранения картинки

		textfiel_load.render(window);

		textfiel_save.render(window);

		window.display();
	}

	return 0;
}