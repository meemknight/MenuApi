//this is a sample of how to use the menu api
//
//(c) Luta Vlad - 2019
//
#include <SFML/Graphics.hpp>
#include "MenuApi.h"
#include <iostream>


int main()
{
	sf::RenderWindow window(sf::VideoMode(1800, 900), "Menu api", sf::Style::Default);
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

	//this is the main menu object. It is mandatory for it to have
	//a pointer to a valid sf::RenderWindow;
	ma::Menu m(&window);
	m.backButton = new ma::IconButton(0, &arrowTexture, 0);
	m.background.setTexture(background);

	ma::MenuHolder mh(&m);
	ma::MenuHolder menu3(&m);

	ma::MenuHolder menu2(&m);
	menu2.appendElement(new ma::TextButton(&texture, font, new ma::Function([] {std::cout << "test\n"; }), "a"));
	menu2.appendElement(new ma::TextButton(&texture, font, nullptr, "b long text................................................"));
	menu2.appendElement(new ma::TextButton(&smallButtonTexture, font, 0, "text", 30));
	menu2.appendElement(new ma::TextButton(&smallButtonTexture, font, &menu3, "more", 30));

	menu3.appendElement(new ma::TextButton(&texture, font, new ma::Function([] {std::cout << "a\n"; }), "a"));
	menu3.appendElement(new ma::TextButton(&texture, font, new ma::Function([] {std::cout << "b\n"; }), "b"));
	menu3.appendElement(new ma::TextButton(&texture, font, new ma::Function([] {std::cout << "c\n"; }), "c"));
	menu3.appendElement(new ma::TextButton(&texture, font, new ma::Function([] {std::cout << "d\n"; }), "d"));

	//this is a horizontal button arangement
	ma::ButtonGroup buttonGroup(&m);
	buttonGroup.appendElement(new ma::TextButton(&smallButtonTexture, font, new ma::Function([] {std::cout << "A\n"; }), "A", 34));
	buttonGroup.appendElement(new ma::TextButton(&smallButtonTexture, font, new ma::Function([] {std::cout << "B\n"; }), "B", 34));
	buttonGroup.appendElement(new ma::IconButton(&smallButtonTexture, &arrowTexture, 0));
	buttonGroup.appendElement(new ma::TextButton(&smallButtonTexture, font, &menu3, ". . .", 30));

	mh.appendElement(new ma::TextButton(&textButton, font, new ma::Function([] {std::cout << "lol\n"; }), "Menu API", 30));
	mh.appendElement(new ma::TextButton(&texture, font, &menu2, "this is like a big text\nand it leads to more", 34));
	mh.appendElement(&buttonGroup);
	m.mainMenu = &mh;
	mh.appendElement(new ma::TextButton(&texture, font, 0, "b long text................................................"));

	//I recomant not changing the layout of the menu while
	//it is running because it might break it's internal behavour.
	//If you do so and have problems try using Menu::resetStack() function
	//which clears it's state.

	bool mouseButtonPressed = 0;
	bool escapeButtonReleased = 0;
	while (window.isOpen())
	{
		mouseButtonPressed = 0;
		escapeButtonReleased = 0;
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
			}else 
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Escape) { escapeButtonReleased = 1; }
			}
		}

		//if the back button is pressed and you are in the main menu,
		//this function will return false.
		if(!m.update(mouseButtonPressed, escapeButtonReleased))
		{
			window.close();
		}
		
		window.display();
		window.clear();

	}

	return 0;
}