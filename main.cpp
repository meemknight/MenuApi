//this is a sample of how to use the menu api
//											/
//(c) Luta Vlad - 2019						/
//											/


#include <SFML/Graphics.hpp>
#include "MenuApi.h"
#include <iostream>

//this is for testing the Api with all function objects
struct Functor
{
	int element = 0;
	void operator()()
	{
		std::cout << element << "\n";
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1800, 900), "Menu api", sf::Style::Default);
	
	//here i am loading some textures in the most basic manner possible
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


	//this is the main menu holder. All menu holders must have a pointer to the Menu object
	ma::MenuHolder mh(&m);

	ma::MenuHolder menu3(&m);
	ma::MenuHolder menu2(&m);
	
	//here i am appending buttons to the second menu, a lot of them
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
	bool onOffData = 0;
	bool onOffData2 = 0;

	//the OnOffButton can be on or off and writes to a boll variable that you supply the adress of
	buttonGroup.appendElement(new ma::OnOffButton(&smallButtonTexture, &arrowTexture, nullptr, &onOffData));

	mh.appendElement(new ma::TextButton(&textButton, font, new ma::Function([] {std::cout << "lol\n"; }), "Menu API", 30));
	//Here i added a button with the third argument another menu.
	//This means that clicking this button gets you to the third menu.
	mh.appendElement(new ma::TextButton(&texture, font, &menu2, "this is like a big text\nand it leads to more", 34));
	mh.appendElement(&buttonGroup);

	auto choice = new ma::ButtonChoiceGroup(&m);
	choice->notChosenBackground.setTexture(smallButtonTexture);
	choice->chosenBackground.setTexture(smallButtonTexture);
	choice->chosenBackground.setColor(sf::Color::Blue);

	//the ButtonChoiceGroup is a group of buttons from which only one can be chosen,
	//you have to provide your own place to hold the index that is chosen by allocating it
	//on the stack/heap.
	//an index of -1 = no button is chosen
	//the class will write to the location privided here
	choice->index = new int(-1);

	//here i added buttons to choose from, you can also add functionality to them
	choice->appendElement(new ma::PlainText(font, new ma::Function(Functor{ 4 }) , "lol"));
	choice->appendElement(new ma::PlainText(font, nullptr, "2"));
	choice->appendElement(new ma::PlainText(font, nullptr, "3"));
	choice->appendElement(new ma::PlainText(font, nullptr, "4"));

	mh.appendElement(choice);
	
	m.mainMenu = &mh;
	mh.appendElement(new ma::TextButton(&texture, font, 0, "b long text................................................"));

	//I recomant not changing the layout of the menu while
	//it is running because it might break it's internal behavour.
	//If you do so and have problems try using Menu::resetStack() function
	//which clears it's state.

	auto size = window.getSize();

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
			}else
			if(event.type == sf::Event::Resized)
			{
				 size = window.getSize();
			}
		}

		//if the back button is pressed and you are in the main menu,
		//this function will return false.
		//the arguments could be just false if you foor example don't want to use escape to go back.
		if(!m.update(mouseButtonPressed, escapeButtonReleased))
		{
			window.close();
		}
		
		window.setView(sf::View({ 0.f, 0.f, (float)size.x, (float)size.y }));
		window.display();
		window.clear();

	}

	return 0;
}