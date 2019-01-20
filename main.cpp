#include <SFML/Graphics.hpp>
#include "MenuApi.h"

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


	mh.appendElement(new ma::TextButton(&texture, font, "a"));
	mh.appendElement(new ma::TextButton(&texture, font, "test"));
	mh.appendElement(new ma::TextButton(&texture, font, "b"));
	mh.appendElement(new ma::TextButton(&texture, font, "c"));
	mh.appendElement(new ma::TextButton(&texture, font, "asta e lung"));

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