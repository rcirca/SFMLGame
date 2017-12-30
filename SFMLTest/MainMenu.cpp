#include "MainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow &window)
{
	sf::Texture texture;
	texture.loadFromFile("images/Mainmenu.png");
	sf::Sprite sprite(texture);

	MenuItem playButton;
	playButton.rect.top = 145;
	playButton.rect.height = 233;
	playButton.rect.left = 0;
	playButton.rect.width = 1023;
	playButton.action = MainMenu::MenuResult::Play;

	MenuItem exitButton;
	exitButton.rect.top = 383;
	exitButton.rect.height = 185;
	exitButton.rect.left = 0;
	exitButton.rect.width = 1023;
	exitButton.action = MainMenu::MenuResult::Exit;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow &window)
{
	sf::Event menuEvent;

	while (true)
	{
		while (window.pollEvent(menuEvent)) 
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			if (menuEvent.type == sf::Event::Closed)
				return MainMenu::MenuResult::Exit;
		}
	}
}


MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator iterator;
	for (iterator = _menuItems.begin(); iterator != _menuItems.end(); iterator++)
	{
		sf::Rect<int> menuItemRect = iterator->rect;
		if (menuItemRect.contains(x, y))
			return iterator->action;
	}

	return MainMenu::MenuResult::Nothing;
}