//////////////////////////////////////////////////////////////////
//MenuApi.h
//(c) Luta Vlad - 2019
// this library is under MIT license, do not remove this notice
//https://github.com/meemknight/MenuApi
//////////////////////////////////////////////////////////////////
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

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
		function,
		iconButton,
		buttonGroup
	};

	class ButtonAccesseble
	{
	public:
		ButtonAccesseble() {};

		virtual int getType() = 0;
		virtual void execute() = 0;
	};

	///bref this is the main menu class in where you will be storing your menu group.
	///It needs to have a pointer to a MenuHolder in where you will put your buttons.
	class Menu
	{
	public:
		Menu() {}
		Menu(sf::RenderWindow *window) :window(window){}

		//the first element of the pair is the index in menu, the second is the index in the subGroup
		std::vector<std::pair<int, int>> stack;
		MenuHolder *mainMenu = 0;
		MenuElement *backButton = 0;

		sf::RenderWindow *window = 0;
		sf::Sprite background;

		int update(bool mouseReleased, bool escapeReleased = 0);
		void resetStack() { stack.clear(); }
	};


	class MenuElement
	{
	public:
		MenuElement() {};

		virtual void draw(sf::RenderWindow *window) = 0;
		virtual int checkInput(sf::RenderWindow *window, bool mouseReleased);
		virtual int getType() = 0;
		virtual Point getSize() = 0;
		virtual void setPositionX(int x) = 0;
		virtual void setPositionY(int y) = 0;
		virtual int getPositionX() = 0;
		virtual int getPositionY() = 0;
		//Menu *context;
		ButtonAccesseble *actionType = 0;
	};


	///bref this class can hold other menu elements inside it.
	///It must have a refference to it's Menu since it needs to know things like the size of
	///the window.
	class MenuHolder : public  ButtonAccesseble
	{
	protected:
		std::vector<MenuElement*> elements;
	public:
		MenuHolder(Menu *menu = nullptr):menu(menu) {};
		
		Menu *menu;

		void appendElement(MenuElement *e);
		void updateElementsPosition();

		int getType() override { return type::menuHolder; }
		void execute() override {};

		friend Menu;
	};

	///bref this is a function that is accessed by a clicked button
	class Function : public  ButtonAccesseble
	{
	public:
		Function() {};
		Function(void(*functionPointer)()) :functionPointer(functionPointer) {};

		void(*functionPointer)() = nullptr;

		virtual int getType() override{ return type::function; };
		virtual void execute() override;
	};

	///bref this is a button with some text in it
	class TextButton : public virtual MenuElement
	{
	protected:
		sf::Font font;
	public:
		TextButton() {};
		TextButton(sf::Texture *t, sf::Font f, ButtonAccesseble* action, const char* text = nullptr, int textSize = 30, sf::Color color = sf::Color::Black)			
		{
			actionType = action;
			if( t!= nullptr)
			{
				s.setTexture(*t);
			}

			font = f;
			textContent.setCharacterSize(textSize);
			textContent.setFillColor(color);
			textContent.setFont(font);
			if(text)
			{
				textContent.setString(text);
			}
		}

		sf::Sprite s;
		sf::Text textContent;


		virtual void draw(sf::RenderWindow *window) override;
		virtual int getType() override { return type::textButton; }
		virtual Point getSize() override;
		virtual void setPositionX(int x) override;
		virtual void setPositionY(int y) override;
		virtual int getPositionX() override;
		virtual int getPositionY() override;
	};

	///bref this is a button with a sprite in it
	class IconButton : public virtual MenuElement
	{
	public:
		IconButton() {};
		IconButton(sf::Texture *background, sf::Texture *foreground, ButtonAccesseble* action)
		{
			actionType = action;
			
			if (background != nullptr)
			{
				backgroundSprite.setTexture(*background);
			}

			if(foreground != nullptr)
			{
				foregroundSprite.setTexture(*foreground);
			}
		}

		sf::Sprite backgroundSprite;
		sf::Sprite foregroundSprite;


		virtual void draw(sf::RenderWindow *window) override;
		virtual int getType() override { return type::iconButton; }
		virtual Point getSize() override;
		virtual void setPositionX(int x) override;
		virtual void setPositionY(int y) override;
		virtual int getPositionX() override;
		virtual int getPositionY() override;
	
	};

	///bref this is an horizontal group of buttons.
	///I reccomand using it with small buttons.
	class ButtonGroup : public MenuElement
	{
	protected:

		//the second element from the pair is just an offset from the first one
		std::vector<std::pair<MenuElement*, int>> buttons;
	public:
		ButtonGroup() {};
		ButtonGroup(Menu *menu):menu(menu) {};
		
		void appendElement(MenuElement *element);
		void updateElementsPosition();

		Menu *menu;

		virtual void draw(sf::RenderWindow *window) override;
		virtual int getType() override { return type::buttonGroup; }
		virtual Point getSize() override;
		virtual void setPositionX(int x) override;
		virtual void setPositionY(int y) override;
		virtual int getPositionX() override;
		virtual int getPositionY() override;
		virtual int checkInput(sf::RenderWindow *window, bool mouseReleased) override;
	
		friend Menu;
	};



}
