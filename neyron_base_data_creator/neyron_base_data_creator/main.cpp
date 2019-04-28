#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
	//создание главного окна приложения
	RenderWindow window(VideoMode(1200, 720), "NeyronBaseDataCreator");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}

	return 0;
}
