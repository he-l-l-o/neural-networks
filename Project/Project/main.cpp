#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
	// ������� ������� ���� ����������
	RenderWindow window(VideoMode(1000, 600), "NeuralNetworks");

	Image MenuImage;//������� ����
	MenuImage.loadFromFile("images/menu.png");
	Image LoadpapImage;//������ ��������
	LoadpapImage.loadFromFile("images/Loadpap.png");
	Image SavepapImage;//������ ����������
	SavepapImage.loadFromFile("images/Save.png");
	Image LoadImage;//������� ��������
	LoadImage.loadFromFile("images/LoadImage.jpg");
	double size_of_x = LoadImage.getSize().x, size_of_y = LoadImage.getSize().y;//��������� ������� ��������
	double ratio = size_of_x / size_of_y; // ��������� x � y
	
	int save_size_of_x = size_of_x, save_size_of_y = size_of_y;//��������� ���-�� ��������

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

	Texture MenuImageTexture;//������� �������� ����
	MenuImageTexture.loadFromImage(MenuImage);
	Texture LoadpapImageTexture;//������� �������� ������ ��������
	LoadpapImageTexture.loadFromImage(LoadpapImage);
	Texture SavepapImageTexture;//������� �������� ������ ����������
	SavepapImageTexture.loadFromImage(SavepapImage);
	Texture LoadImageTexture;//������� �������� ����������� ��������
	LoadImageTexture.loadFromImage(LoadImage);
	
	Sprite MenuImageSprite; //������� ������ ����
	MenuImageSprite.setTexture(MenuImageTexture);
	MenuImageSprite.setPosition(0, 0);
	Sprite LoadpapImageSprite; //������� ������ ������ ��������
	LoadpapImageSprite.setTexture(LoadpapImageTexture);
	LoadpapImageSprite.setPosition(422, 532);
	Sprite SavepapImageSprite; //������� ������ ������ ����������
	SavepapImageSprite.setTexture(SavepapImageTexture);
	SavepapImageSprite.setPosition(952, 532);
	Sprite LoadImageSprite; //������� ������ ����������� ��������
	LoadImageSprite.setTexture(LoadImageTexture);
	LoadImageSprite.setPosition(23, 23);

	Vector2f targetSize(size_of_x, size_of_y); //������� �����p
	LoadImageSprite.setScale(
		targetSize.x / LoadImageSprite.getGlobalBounds().width,
		targetSize.y / LoadImageSprite.getGlobalBounds().height);

	// ������� ���� ����������
	while (window.isOpen())
	{
		// ������������ ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			// ����� �������� ������� ���� ���� ����� ����������� �� ������� �� Escape
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

		// �������
		window.clear();
		// ��� ����� ���������� ������� ���������� � ��������� ��������
		// ���������
		window.draw(MenuImageSprite);//������ ����
		
		window.draw(LoadpapImageSprite);//������ ������ �����

		window.draw(SavepapImageSprite);//������ ������ ����������

		window.draw(LoadImageSprite);//������ ����������� ��������

		window.display();
	}
	return 0;
}