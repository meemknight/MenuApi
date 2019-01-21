#include "MenuApi.h"


namespace ma
{

#pragma region MenuElement
	///check input should return 1 if a button was pressed and it was a menuHolder
	/// 0 if nothing was pressed
	/// 2 if a normal button was pressd
	/// 3 if the button was just pressed
	int MenuElement::checkInput(sf::RenderWindow * window, bool mouseReleased)
	{
		if (mouseReleased)
		{
			sf::IntRect rect(getPositionX(), getPositionY(), getSize().x, getSize().y);	
			if (rect.contains(sf::Mouse::getPosition(*window)))
			{
				if (actionType != nullptr)
				{
					if (actionType->getType() == type::function)
					{
						actionType->execute();
						return 2;
					}
					else if (actionType->getType() == type::menuHolder)
					{
						return 1;
					}
				}else
				{
					return 3;
				}
			}
		}

		return 0;
	}

#pragma endregion

	int Menu::update(bool mouseReleased)
	{
		MenuHolder *holder;
		holder = mainMenu;

		if (stack.size() != 0)
		{
			for (int i = 0; i < stack.size(); i++)
			{
				if (holder->elements[stack[i]]->actionType->getType() == type::menuHolder)
				{
					holder = (MenuHolder*)holder->elements[stack[i]]->actionType;
				}
				else
				{

				}
			}

		}


		int input = -1;
		for (int i = holder->elements.size() - 1; i >= 0; i--)
		{
			holder->elements[i]->draw(window);
			int temp = holder->elements[i]->checkInput(window, mouseReleased);
			if (temp == 1)
			{
				input = i;
			}
		}

		if (input != -1)
		{
			stack.push_back(input);
		}

		if(backButton != nullptr)
		{
			backButton->setPositionX(100);
			backButton->setPositionY(100);
			backButton->draw(window);
			if(backButton->checkInput(window, mouseReleased) > 0)
			{
				if(stack.size()==0)
				{
					return 0;
				}

				stack.pop_back();
			}

		}

		return 1;
	}



#pragma region MenuHolder

	

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
#pragma endregion

#pragma region TextButton

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

	Point TextButton::getSize()
	{
		if(s.getTexture() == nullptr)
		{
			return { 0,0 };
		}
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
#pragma endregion

#pragma region Function
	void Function::execute()
	{
		if (functionPointer != nullptr)
		{
			functionPointer();
		}
	}
#pragma endregion

#pragma region IconButton

	void IconButton::draw(sf::RenderWindow * window)
	{
		window->draw(backgroundSprite);
		window->draw(foregroundSprite);
	}


	Point IconButton::getSize()
	{
		auto sizeF = sf::Vector2u();
		if(foregroundSprite.getTexture() == nullptr)
		{
			sizeF = { 0,0 };
		}else
		{
			sizeF = foregroundSprite.getTexture()->getSize();
		}

		auto sizeB = sf::Vector2u();
		if (backgroundSprite.getTexture() == nullptr)
		{
			sizeB = { 0,0 };
		}
		else
		{
			sizeB = backgroundSprite.getTexture()->getSize();
		}
		
	
		
		if (sizeB.x > sizeF.x) { sizeF.x = sizeB.x; }
		if (sizeB.y > sizeF.y) { sizeF.y = sizeB.y; }

		return Point({ (int)sizeF.x, (int)sizeF.y });
	}

	void IconButton::setPositionX(int x)
	{
		backgroundSprite.setPosition({ (float)x, (float)backgroundSprite.getPosition().y });
		foregroundSprite.setPosition({ (float)x, (float)foregroundSprite.getPosition().y });
	}

	void IconButton::setPositionY(int y)
	{
		backgroundSprite.setPosition({ (float)backgroundSprite.getPosition().x, (float)y });
		foregroundSprite.setPosition({ (float)foregroundSprite.getPosition().x, (float)y });
	}

	int IconButton::getPositionX()
	{
		//todo ?
		return backgroundSprite.getPosition().x;
	}

	int IconButton::getPositionY()
	{
		return backgroundSprite.getPosition().y;
	}
#pragma endregion

}

