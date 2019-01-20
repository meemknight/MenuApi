#include "MenuApi.h"


namespace ma
{
	void Menu::update()
	{
		MenuHolder *holder;
		holder = mainMenu;

		if (stack.size() != 0)
		{
			for(int i=0; i<stack.size(); i++)
			{
				if(holder->elements[stack[i]]->actionType->getType() == type::menuHolder)
				{
					holder = (MenuHolder*)holder->elements[stack[i]]->actionType;
				}else
				{
					
				}
			}

	

		}


		int input = -1;
		for(int i = holder->elements.size()-1; i>=0; i--)
		{
			holder->elements[i]->draw(window);
			int temp = holder->elements[i]->checkInput(window);
			if(temp != -1)
			{
				input = i;
			}
		}

		if(input != -1)
		{
			stack.push_back(input);
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
		for(int i = 0; i < elements.size(); i++)
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
		auto startingPos = s.getPosition();
		int spareX = getSize().x;	
		int spareY = getSize().y;

		spareY -= textContent.getCharacterSize();
		spareY /= 2;
		startingPos.y += spareY;

		spareX -= textContent.getCharacterSize() * textContent.getString().getSize() / 2;
		spareX /= 2;
		startingPos.x += spareX;

		textContent.setPosition(startingPos);
		window->draw(textContent);

	}

	int TextButton::checkInput(sf::RenderWindow *window)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::IntRect rect(getPositionX(), getPositionY(), getSize().x, getSize().y);
			if(rect.contains(sf::Mouse::getPosition(*window)))
			{
				if(actionType->getType() == type::function)
				{
					actionType->execute();
				}else if(actionType->getType() == type::menuHolder)				
				{
					return 1;
				}
			}
		}

		return -1;
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

	int TextButton::getPositionX()
	{
		return s.getPosition().x;
	}

	int TextButton::getPositionY()
	{
		return s.getPosition().y;
	}


	void Function::execute()
	{
		if(functionPointer!=nullptr)
		{
			functionPointer();
		}
	}

}

