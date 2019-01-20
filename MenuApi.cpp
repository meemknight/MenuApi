#include "MenuApi.h"

namespace ma
{
	void Menu::update()
	{
		MenuHolder *holder;

		//if (stack.size() != 0)
		//{
		//
		//}else
		//{
		//	holder = mainMenu;
		//}

		holder = mainMenu;


		for(auto i: holder->elements)
		{
			i->draw(window);
		
		}

	}



	void MenuHolder::appendElement(MenuElement * e)
	{
		elements.push_back(e);
		updateElementsPosition();
	}

	void MenuHolder::updateElementsPosition()
	{
		int spareSpace = menu->window->getSize().y;

		for (int i = elements.size()-1; i >= 0; i--)
		{
			spareSpace -= elements[i]->getSize().y;
		}

		int padding;
		if(spareSpace > 0)
		{
			 padding = spareSpace / (elements.size() + 1);
		}else
		{
			padding = 0;
		}

		int pos = 0;
		for(int i = elements.size()-1; i >= 0; i--)
		{
			pos += padding;
			elements[i]->setPositionY(pos);
			elements[i]->setPositionX(((menu->window->getSize().x) / 2) - (elements[i]->getSize().x / 2));
			pos += elements[i]->getSize().y;
		}

	}


	void TextButton::draw(sf::RenderWindow *window)
	{
		window->draw(s);
		textContent.setPosition(s.getPosition());
		window->draw(textContent);

	}

	int TextButton::checkInput()
	{
		return 0;
	}

	Point TextButton::getSize()
	{
		auto size = s.getTexture()->getSize();
		return Point({(int)size.x, (int)size.y});
	}

	void TextButton::setPositionX(int x)
	{
		s.setPosition({ (float)x, (float)s.getPosition().y });
	}

	void TextButton::setPositionY(int y)
	{
		s.setPosition({ (float)s.getPosition().x, (float)y });
	}


}

