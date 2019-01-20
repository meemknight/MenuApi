#include <SFML/Graphics.hpp>
#include "MenuApi.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1800, 800), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	sf::Texture texture;
	texture.loadFromFile("button.png");
	sf::Font font;
	font.loadFromFile("font.ttf");

	ma::Menu m;
	m.window = &window;

	ma::MenuHolder mh;
	mh.menu = &m;

	ma::MenuHolder menu2;
	menu2.menu = &m;
	menu2.appendElement(new ma::TextButton(&texture, font, new ma::Function([] {}), "a"));
	menu2.appendElement(new ma::TextButton(&texture, font, new ma::Function([] {}), "b"));



	mh.appendElement(new ma::TextButton(&texture, font, new ma::Function([]{}), "a"));
	mh.appendElement(new ma::TextButton(&texture, font, new ma::Function([]{}), "test"));
	mh.appendElement(new ma::TextButton(&texture, font, new ma::Function([]{}), "b"));
	mh.appendElement(new ma::TextButton(&texture, font, &menu2, "asta e gen un text f f lung si mare", 30));
	mh.appendElement(new ma::TextButton(&texture, font, new ma::Function([] {std::cout << "lol\n"; }), "asta e lung"));

	m.mainMenu = &mh;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		
		}
		


		window.draw(shape);
		m.update();
		
		window.display();
		window.clear();

	}

	return 0;
}