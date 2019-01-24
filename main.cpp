#include <SFML/Graphics.hpp>
#include "MenuApi.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1800, 900), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	sf::Texture texture;
	texture.loadFromFile("button.png");

	sf::Texture smallButtonTexture;
	smallButtonTexture.loadFromFile("smallButton.png");

	sf::Texture arrowTexture;
	arrowTexture.loadFromFile("backButton.png");

	sf::Texture textButton;
	textButton.loadFromFile("textBUtton.png");

	sf::Font font;
	font.loadFromFile("horrendo.ttf");

	sf::Texture background;
	background.loadFromFile("background.png");

	ma::Menu m;
	m.window = &window;
	m.backButton = new ma::IconButton(0, &arrowTexture, 0);
	m.background.setTexture(background);

	ma::MenuHolder mh;
	mh.menu = &m;

	ma::MenuHolder menu2;
	menu2.menu = &m;
	menu2.appendElement(new ma::TextButton(&texture, font, new ma::Function([] {std::cout << "test\n"; }), "a"));
	menu2.appendElement(new ma::TextButton(&texture, font, nullptr, "b"));

	ma::MenuHolder menu3;
	menu3.menu = &m;
	menu3.appendElement(new ma::TextButton(&texture, font, new ma::Function([] {std::cout << "a\n"; }), "a"));
	menu3.appendElement(new ma::TextButton(&texture, font, new ma::Function([] {std::cout << "b\n"; }), "b"));
	menu3.appendElement(new ma::TextButton(&texture, font, new ma::Function([] {std::cout << "c\n"; }), "c"));
	menu3.appendElement(new ma::TextButton(&texture, font, new ma::Function([] {std::cout << "d\n"; }), "d"));


	ma::ButtonGroup buttonGroup(&m);
	buttonGroup.appendElement(new ma::TextButton(&smallButtonTexture, font, new ma::Function([] {std::cout << "A\n"; }), "A", 34));
	buttonGroup.appendElement(new ma::TextButton(&smallButtonTexture, font, new ma::Function([] {std::cout << "B\n"; }), "B", 34));
	buttonGroup.appendElement(new ma::IconButton(&smallButtonTexture, &arrowTexture, 0));
	buttonGroup.appendElement(new ma::TextButton(&smallButtonTexture, font, &menu3, ". . .", 30));

	//mh.appendElement(new ma::TextButton(&texture, font, new ma::Function([]{}), "a"));
	//mh.appendElement(new ma::TextButton(&texture, font, new ma::Function([]{}), "test"));
	mh.appendElement(new ma::TextButton(&textButton, font, new ma::Function([] {std::cout << "lol\n"; }), "Menu API", 30));
	mh.appendElement(new ma::TextButton(&texture, font, &menu2, "this is like a big text", 34));
	mh.appendElement(&buttonGroup);
	m.mainMenu = &mh;
	mh.appendElement(new ma::TextButton(&texture, font, 0, "a"));


	bool mouseButtonPressed = 0;
	while (window.isOpen())
	{
		mouseButtonPressed = 0;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}else
			if(event.type == sf::Event::MouseButtonReleased)
			{
				if (event.key.code == sf::Mouse::Left) { mouseButtonPressed = 1; }
			}

		}

		if(!m.update(mouseButtonPressed))
		{
			window.close();
		}
		
		window.display();
		window.clear();

	}

	return 0;
}