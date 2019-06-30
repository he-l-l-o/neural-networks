#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "ratio.h"
#include "../..//neyron_base_data_creator/neyron_base_data_creator/textfield.h"
#include "../..//algorhytm/algorhytm/neuro.h"

using namespace sf;
using namespace std;

int main()
{
	setlocale(0, "");

	// Создаем главное окно приложения
	RenderWindow window(VideoMode(1000, 600), "NeuralNetworks", Style::Close);

	string string_load; //переменная для ввода текста пути загрузки
	string string_save; //переменная для ввода текста пути сохранения

	Font font; //инициализация шрифта
	font.loadFromFile("Times New Roman.ttf");

	Text text_load(L"", font, 20); //инициализация текста с путем для загрузки
	text_load.setStyle(Text::Bold);
	text_load.setPosition(27, 532);
	Text text_save(L"", font, 20); //инициализация текста с путем для сохранения
	text_save.setStyle(Text::Bold);
	text_save.setPosition(557, 532);

	textfield textfiel_load;
	textfiel_load.set_font(font);
	textfiel_load.set_lenght(33);
	textfiel_load.set_position(sf::Vector2f(22, 532));

	textfield textfiel_save;
	textfiel_save.set_font(font);
	textfiel_save.set_lenght(32);
	textfiel_save.set_position(sf::Vector2f(527, 532));

	Image menu_image; //инициализация изображения меню
	menu_image.loadFromFile("images/menu.png");
	Image load_pap_image; //инициализация изображения кнопки загрузки
	load_pap_image.loadFromFile("images/load_pap.png");
	Image save_pap_image; //инициализация изображения кнопки сохранения
	save_pap_image.loadFromFile("images/save.png");
	Image* load_image = new Image; //инициализация загруженного изображения
	Image* save_image = new Image; //инициализация сохраненного изображения
	Image convert_image;
	convert_image.loadFromFile("images/convert.png");

	Texture menu_image_texture; //инциализация текстуры для menu_image
	menu_image_texture.loadFromImage(menu_image);
	Texture load_pap_image_texture; //инциализация текстуры для load_pap_image
	load_pap_image_texture.loadFromImage(load_pap_image);
	Texture save_pap_image_texture; //инциализация текстуры для save_pap_image
	save_pap_image_texture.loadFromImage(save_pap_image);
	Texture* load_image_texture = new Texture; //создаем текстуру загруженной картинки
	Texture* save_image_texture = new Texture; //Создание текстуры под новое изображение
	Texture convert_texture;
	convert_texture.loadFromImage(convert_image);

	Sprite menu_image_sprite; //инициализация спрайта меню
	menu_image_sprite.setTexture(menu_image_texture);
	menu_image_sprite.setPosition(0, 0);
	Sprite load_pap_image_sprite; //инициализация спрайта кнопки загрузки
	load_pap_image_sprite.setTexture(load_pap_image_texture);
	load_pap_image_sprite.setPosition(450, 532);
	Sprite save_pap_image_sprite; //инициализация спрайта кнопки сохранения
	save_pap_image_sprite.setTexture(save_pap_image_texture);
	save_pap_image_sprite.setPosition(952, 532);
	Sprite* load_image_sprite = new Sprite; //инициализация спрайта загруженной картинки
	Sprite* save_image_sprite = new Sprite; //инициализация спрайта обратботанной картинки
	Sprite convert_sprite;
	convert_sprite.setTexture(convert_texture);
	convert_sprite.setPosition(490, 532);


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
			textfiel_load.input(event, string_load);
			textfiel_save.input(event, string_save);

			load_pap_image_sprite.setColor(Color::White);
			convert_sprite.setColor(Color::White);
			save_pap_image_sprite.setColor(Color::White);

			if (IntRect(450, 532, 27, 27).contains(Mouse::getPosition(window)))
			{
				load_pap_image_sprite.setColor(Color(180, 180, 180, 255));
			}
			if (IntRect(490, 532, 27, 27).contains(Mouse::getPosition(window)))
			{
				convert_sprite.setColor(Color(180, 180, 180, 255));
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
				if (IntRect(490, 532, 26, 26).contains(Mouse::getPosition(window)))
				{
					convert_sprite.setColor(Color(180, 180, 180, 255));
				}
				if (IntRect(952, 532, 26, 26).contains(Mouse::getPosition(window)))
				{
					save_pap_image_sprite.setColor(Color(180, 180, 180, 255));
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (event.mouseButton.x >= 450 && event.mouseButton.x <= 516 &&
						event.mouseButton.y >= 532 && event.mouseButton.y <= 558)
					{
						delete load_image_sprite;
						load_image_sprite = NULL;
						delete load_image_texture;
						load_image_texture = NULL;
						delete load_image;
						load_image = NULL;

						load_image = new Image;
						load_image_texture = new Texture;
						load_image_sprite = new Sprite;
						if (load_image_sprite == NULL)
						{
							return -1;
						}

						load_image->loadFromFile(string_load); //взятие изображения по адресу(строки)

						double size_x = load_image->getSize().x; //Считываем размеры картинки
						double size_y = load_image->getSize().y;
						double ratio = size_x / size_y; // отношение x к y

						int save_size_x = size_x, save_size_y = size_y; //сохраняем кол-во пикселей

						////////////////////////СЖАТИЕ ИЗОБРАЖЕНИЯ ДО РАЗМЕРОВ ОКНА////////////////
						ratio_func(size_x, size_y, ratio); //расчет нового разрешения загруженного изображения
						///////////////////////////////////////////////////////////////////////////

						load_image_texture->loadFromImage(*load_image);

						load_image_sprite->setTexture(*load_image_texture);
						load_image_sprite->setPosition(259 - (size_x / 2), 259 - (size_y / 2)); //установка позиции load_image_sprite

						Vector2f target_size(size_x, size_y); //целевой размеp загружаемого изображения
						load_image_sprite->setScale(
							target_size.x / load_image_sprite->getGlobalBounds().width,
							target_size.y / load_image_sprite->getGlobalBounds().height);

						rectangle_load.setSize(sf::Vector2f(size_x, size_y));
						rectangle_load.setPosition(259 - (size_x / 2), 259 - (size_y / 2));
					}
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (event.mouseButton.x >= 490 && event.mouseButton.x <= 516 &&
						event.mouseButton.y >= 532 && event.mouseButton.y <= 558)
					{
						delete load_image_sprite;
						load_image_sprite = NULL;
						delete load_image_texture;
						load_image_texture = NULL;
						delete load_image;
						load_image = NULL;

						load_image = new Image;
						load_image_texture = new Texture;
						load_image_sprite = new Sprite;
						if (load_image_sprite == NULL)
						{
							return -1;
						}

						load_image->loadFromFile(string_load); //взятие изображения по адресу(строки)

						double size_x = load_image->getSize().x; //Считываем размеры картинки
						double size_y = load_image->getSize().y;
						double ratio = size_x / size_y; // отношение x к y

						int save_size_x = size_x, save_size_y = size_y; //сохраняем кол-во пикселей

						////////////////////////СЖАТИЕ ИЗОБРАЖЕНИЯ ДО РАЗМЕРОВ ОКНА////////////////
						ratio_func(size_x, size_y, ratio); //расчет нового разрешения загруженного изображения
						///////////////////////////////////////////////////////////////////////////

						////////////////////////ТРЕХМЕРНЫЙ ДИНАМИЧЕСКИЙ МАССИВ/////////////////////
						//1)Инициализация
						int*** arr_image = new int** [save_size_y];
						if (arr_image == NULL)
						{
							return 1;
						}
						for (int i = 0; i < save_size_y; i++)
						{
							arr_image[i] = new int* [save_size_x];
							if (arr_image[i] == NULL)
							{
								return 1;
							}
							for (int j = 0; j < save_size_x; j++)
							{
								arr_image[i][j] = new int[3];
								if (arr_image[i][j] == NULL)
								{
									return 1;
								}
							}
						}

						//2)Заполнение
						for (int i = 0; i < save_size_y; i++)
						{
							for (int j = 0; j < save_size_x; j++)
							{
								arr_image[i][j][0] = load_image->getPixel(j, i).r; //Красная часть цветовой модели
								arr_image[i][j][1] = load_image->getPixel(j, i).g; //Зеленая часть цветовой модели
								arr_image[i][j][2] = load_image->getPixel(j, i).b; //Синяя часть цветовой модели
							}
						}
						///////////////////////////////////////////////////////////////////////////

						////////////////////////ТРЕХМЕРНЫЙ ДИНАМИЧЕСКИЙ МАССИВ С РЕЗУЛЬТАТАМИ/////////////////////
						//1)Инициализация
						int*** arr_image_processing = new int** [save_size_y];
						if (arr_image == NULL)
						{
							return 1;
						}
						for (int i = 0; i < save_size_y; i++)
						{
							arr_image_processing[i] = new int* [save_size_x];
							if (arr_image[i] == NULL)
							{
								return 1;
							}
							for (int j = 0; j < save_size_x; j++)
							{
								arr_image_processing[i][j] = new int[3];
								if (arr_image[i][j] == NULL)
								{
									return 1;
								}
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

						load_image_texture->loadFromImage(*load_image);

						delete save_image_sprite;
						save_image_sprite = NULL;
						delete save_image_texture;
						save_image_texture = NULL;
						delete save_image;
						save_image = NULL;

						save_image = new Image;
						save_image_texture = new Texture;
						save_image_sprite = new Sprite;
						if (save_image_sprite == NULL)
						{
							return -1;
						}

						save_image->create(save_size_x, save_size_y, Color(0, 0, 0, 100)); //создание нового изображения

						image_processing(arr_image, arr_image_processing, save_size_x, save_size_y);

						//Создание изображения из массива пискелей
						for (int i = 0; i < save_size_y; i++)
						{
							for (int j = 0; j < save_size_x; j++)
							{
								save_image->setPixel(j, i, Color(arr_image_processing[i][j][0], arr_image_processing[i][j][1], arr_image_processing[i][j][2], 255));
							}
						}

						save_image_texture->loadFromImage(*save_image);

						load_image_sprite->setTexture(*load_image_texture);
						load_image_sprite->setPosition(259 - (size_x / 2), 259 - (size_y / 2)); //установка позиции load_image_sprite

						save_image_sprite->setTexture(*save_image_texture);
						save_image_sprite->setPosition(742 - (size_x / 2), 259 - (size_y / 2)); //установка позиции save_image_sprite

						Vector2f target_size(size_x, size_y); //целевой размеp загружаемого изображения
						load_image_sprite->setScale(
							target_size.x / load_image_sprite->getGlobalBounds().width,
							target_size.y / load_image_sprite->getGlobalBounds().height);
						Vector2f target_size1(size_x, size_y); //целевой размеp обработанного изображения
						save_image_sprite->setScale(
							target_size1.x / save_image_sprite->getGlobalBounds().width,
							target_size1.y / save_image_sprite->getGlobalBounds().height);

						rectangle_load.setSize(sf::Vector2f(size_x, size_y));
						rectangle_save.setSize(sf::Vector2f(size_x, size_y));
						rectangle_load.setPosition(259 - (size_x / 2), 259 - (size_y / 2));
						rectangle_save.setPosition(742 - (size_x / 2), 259 - (size_y / 2));

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
						save_image->saveToFile(string_save); //Сохранение картинки
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

		window.draw(convert_sprite);//рисуем кнопку обратки изображения

		window.draw(save_pap_image_sprite); //рисуем иконку сохранения

		window.draw(rectangle_load); //рисуем рамку изображения

		window.draw(rectangle_save);

		window.draw(*load_image_sprite); //рисуем Загруженную картинку

		window.draw(*save_image_sprite); //рисуем полученную картинку

		textfiel_load.render(window);

		textfiel_save.render(window);

		window.display();
	}

	return 0;
}