#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

int main()
{
	// ������� ������� ���� ����������
	RenderWindow window(VideoMode(1000, 600), "NeuralNetworks");

	string stroka_load;//���������� ��� ����� ������ ���� ��������
	string stroka_save;//���������� ��� ����� ������ ���� ����������

	Font font;//������������� ������
	font.loadFromFile("Times New Roman.ttf");//�������� ���� � ������� � font 
	
	Text text_load("", font, 20);//������������� ������ � ����� ��� ��������
	text_load.setStyle(Text::Bold);//������ ����� �������� ������
	text_load.setPosition(27, 532);//�������������� ������ ��������
	Text text_save("", font, 20);//������������� ������ � ����� ��� ����������
	text_save.setStyle(Text::Bold);//������ ����� �������� ������
	text_save.setPosition(557, 532);//�������������� ������ ��������

	Image menu_image;//������������� ����������� ����
	menu_image.loadFromFile("images/menu.png");//�������� ����������� � menu_image
	Image load_pap_image;//������������� ����������� ������ ��������
	load_pap_image.loadFromFile("images/Loadpap.png");//�������� ����������� � load_pap_image
	Image save_pap_image;//������������� ����������� ������ ����������
	save_pap_image.loadFromFile("images/Save.png");//�������� ����������� � save_pap_image
	Image load_image;//������������� ������������ �����������
	Image save_image;//������������� ������������ �����������
	
	Texture menu_image_texture;//������������ �������� ��� menu_image
	menu_image_texture.loadFromImage(menu_image);//�������� menu_image � menu_image_texture
	Texture load_pap_image_texture;//������������ �������� ��� load_pap_image
	load_pap_image_texture.loadFromImage(load_pap_image);//�������� load_pap_image � load_pap_image_texture
	Texture save_pap_image_texture;//������������ �������� ��� save_pap_image
	save_pap_image_texture.loadFromImage(save_pap_image);//�������� save_pap_image � save_pap_image_texture
	Texture load_image_texture;//������� �������� ����������� ��������
	Texture save_image_texture;//�������� �������� ��� ����� �����������

	Sprite menu_image_sprite; //������������� ������� ����
	menu_image_sprite.setTexture(menu_image_texture);
	menu_image_sprite.setPosition(0, 0);
	Sprite load_pap_image_sprite; //������������� ������� ������ ��������
	load_pap_image_sprite.setTexture(load_pap_image_texture);
	load_pap_image_sprite.setPosition(422, 532);
	Sprite save_pap_image_sprite; //������������� ������� ������ ����������
	save_pap_image_sprite.setTexture(save_pap_image_texture);
	save_pap_image_sprite.setPosition(952, 532);
	Sprite load_image_sprite; //������������� ������� ����������� ��������
	Sprite save_image_sprite; //������������� ������� ������������� ��������

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
						
						getline(cin, stroka_load);//���������� ����
						
						load_image.loadFromFile(stroka_load);//������ ����������� �� ������(������)

						double size_x = load_image.getSize().x, size_y = load_image.getSize().y;//��������� ������� ��������
						double ratio = size_x / size_y; // ��������� x � y

						int save_size_x = size_x, save_size_y = size_y;//��������� ���-�� ��������

						////////////////////////������ ����������� �� �������� ����////////////////
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

						////////////////////////���������� ������������ ������/////////////////////
						//1)�������������
						int ***arr_image = new int **[save_size_y];
						for (int i = 0; i < save_size_y; i++)
						{
							arr_image[i] = new int *[save_size_x];
							for (int j = 0; j < save_size_x; j++)
								arr_image[i][j] = new int[3];
						}
						//2)����������
						for (int i = 0; i < save_size_y; i++)
						{
							for (int j = 0; j < save_size_x; j++)
							{
								arr_image[i][j][0] = load_image.getPixel(j, i).r; //������� ����� �������� ������
								arr_image[i][j][1] = load_image.getPixel(j, i).g; //������� ����� �������� ������
								arr_image[i][j][2] = load_image.getPixel(j, i).b; //����� ����� �������� ������
							}
						}
						///////////////////////////////////////////////////////////////////////////
					
						load_image_texture.loadFromImage(load_image);//�������� load_image � load_image_texture

						save_image.create(save_size_x, save_size_y, Color(255, 255, 100, 100));//�������� ������ �����������

						//�������� ����������� �� ������� ��������
						for (int i = 0; i < save_size_y; i++) {
							for (int j = 0; j < save_size_x; j++) {
								save_image.setPixel(j, i, Color(arr_image[i][j][0], arr_image[i][j][1], arr_image[i][j][2], 255));
							}
						}

						save_image_texture.loadFromImage(save_image);//�������� save_image � save_image_texture
					
						load_image_sprite.setTexture(load_image_texture);//�������� load_image_texture � load_image_texture
						load_image_sprite.setPosition(23, 23);//��������� ������� load_image_sprite
						
						save_image_sprite.setTexture(save_image_texture);//�������� save_image_texture � save_image_sprite 
						save_image_sprite.setPosition(503, 23);//��������� ������� save_image_sprite

						Vector2f target_size(size_x, size_y); //������� �����p ������������ �����������
						load_image_sprite.setScale(
							target_size.x / load_image_sprite.getGlobalBounds().width,
							target_size.y / load_image_sprite.getGlobalBounds().height);
						Vector2f target_size1(size_x, size_y); //������� �����p ������������� �����������
						save_image_sprite.setScale(
							target_size1.x / save_image_sprite.getGlobalBounds().width,
							target_size1.y / save_image_sprite.getGlobalBounds().height);

						//������������ ������
						for (int i = 0; i < save_size_y; i++) {
							for (int j = 0; j < save_size_x; j++) {
								delete[] arr_image[i][j];
							}
							delete[] arr_image[i];
						}
						delete[] arr_image;
					}
				}
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (event.mouseButton.x >= 952 && event.mouseButton.x <= 978 && event.mouseButton.y >= 532 && event.mouseButton.y <= 558) {
						cout << "the right button was pressed on Save" << endl;
						cout << "mouse x: " << event.mouseButton.x << endl;
						cout << "mouse y: " << event.mouseButton.y << endl;

						getline(cin, stroka_save);//���������� ����

						save_image.saveToFile(stroka_save/*"images/SaveImage.jpg"*/);//���������� ��������
					}
				}
			}
		}

		// �������
		window.clear();
		// ��� ����� ���������� ������� ���������� � ��������� ��������
		// ���������
		window.draw(menu_image_sprite);//������ ����

		window.draw(load_pap_image_sprite);//������ ������ �����

		window.draw(save_pap_image_sprite);//������ ������ ����������
		
		window.draw(load_image_sprite);//������ ����������� ��������

		window.draw(save_image_sprite);//������ ���������� ��������

		text_load.setString(stroka_load);//�������� stroka_load � text_load
		window.draw(text_load);//������ ����� ��� �������� ��������
		
		text_save.setString(stroka_save);//�������� stroka_save � text_save
		window.draw(text_save);//������ ����� ��� ���������� ��������

		window.display();
	}

	return 0;
}