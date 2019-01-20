#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace ma
{
	class MenuHolder;
	class TextButton;
	class MenuElement;
	class Menu;
	class ButtonAccesseble;

	struct Point
	{
		int x;
		int y;
	};

	enum type
	{
		none = 0,
		menuHolder,
		textButton,
	};

	class ButtonAccesseble
	{
	public:
		ButtonAccesseble() {};

		virtual int getType() = 0;
		virtual void execute() = 0;
	};

	class Menu
	{
	public:
		Menu() {}

		std::vector<int> stack;
		MenuHolder *mainMenu;


		sf::RenderWindow *window;

		void update();

	};

	

	class MenuElement
	{
	public:
		MenuElement() {};

		virtual void draw(sf::RenderWindow *window) = 0;
		virtual int checkInput() = 0;
		virtual int getType() = 0;
		virtual Point getSize() = 0;
		virtual void setPositionX(int x) = 0;
		virtual void setPositionY(int y) = 0;
		Menu *context;
	};

	class MenuHolder : public virtual ButtonAccesseble
	{
	protected:
		std::vector<MenuElement*> elements;
	public:
		MenuHolder() {};
		
		Menu *menu;

		void appendElement(MenuElement *e);
		void updateElementsPosition();

		int getType() override { return type::menuHolder; }
		void execute() override {};

		friend Menu;
	};

	class TextButton : public virtual MenuElement
	{
	protected:
		sf::Font font;
	public:
		TextButton() {};
		TextButton(sf::Texture *t, sf::Font f, const char* text = nullptr, int textSize = 24)
		{
			s.setTexture(*t);
			font = f;
			textContent.setCharacterSize(textSize);
			textContent.setFont(font);
			if(text)
			{
				textContent.setString(text);
			}
		}

		sf::Sprite s;
		sf::Text textContent;

		
		void draw(sf::RenderWindow *window) override;
		int checkInput();
		int getType() { return type::textButton; }
		Point getSize();
		void setPositionX(int x);
		void setPositionY(int y);
	};
}
