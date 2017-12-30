#include "SplashScreen.h"


void SplashScreen::Show(sf::RenderWindow &window)
{
	sf::Texture splashTexture;
	if (!splashTexture.loadFromFile("images/SplashScreen.png"))
		return;

	sf::Sprite sprite(splashTexture);

	window.draw(sprite);
	window.display();
	sf::Event event;
	while (true)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed
				|| event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed)
				return;
		}
	}
}