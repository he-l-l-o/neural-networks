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

	Texture MenuImageTexture;//������� �������� ����
	MenuImageTexture.loadFromImage(MenuImage);
	Texture LoadpapImageTexture;//������� �������� ������ ��������
	LoadpapImageTexture.loadFromImage(LoadpapImage);
	Texture SavepapImageTexture;//������� �������� ������ ����������
	SavepapImageTexture.loadFromImage(SavepapImage);
	
	Sprite MenuImageSprite; //������� ������ ����
	MenuImageSprite.setTexture(MenuImageTexture);
	MenuImageSprite.setPosition(0, 0);
	Sprite LoadpapImageSprite; //������� ������ ������ ��������
	LoadpapImageSprite.setTexture(LoadpapImageTexture);
	LoadpapImageSprite.setPosition(422, 532);
	Sprite SavepapImageSprite; //������� ������ ������ ����������
	SavepapImageSprite.setTexture(SavepapImageTexture);
	SavepapImageSprite.setPosition(952, 532);

	// ������� ���� ����������
	while (window.isOpen())
	{
		// ������������ ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			// ����� �������� ������� ���� ���� ����� ����������� �� ������� �� Escape
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
				window.close();
		}

		// �������
		window.clear();
		// ��� ����� ���������� ������� ���������� � ��������� ��������
		// ���������
		window.draw(MenuImageSprite);//������ ����
		
		window.draw(LoadpapImageSprite);//������ ������ �����

		window.draw(SavepapImageSprite);//������ ������ ����������

		window.display();
	}
	return 0;
}