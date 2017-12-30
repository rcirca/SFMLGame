#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"

void Game::Start()
{
	if (_gameState != Game::Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1024, 768, 32), "Pang!");
	_gameState = Game::ShowingSplash;
	_paddle1.load("images/paddle.png");
	_paddle1.setPosition((1024 / 2) - 45, 700);

	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop()
{
	switch (_gameState)
	{
		case Game::Playing:
		{
			sf::Event currentEvent;
			while (_mainWindow.pollEvent(currentEvent))
			{
				_mainWindow.clear(sf::Color(0, 0, 0));
				_paddle1.draw(_mainWindow);
				_mainWindow.display();

				if (currentEvent.type == sf::Event::Closed)
					_gameState = Game::Exiting;

				if (currentEvent.type == sf::Event::KeyPressed)
					if (currentEvent.key.code == sf::Keyboard::Escape)
						ShowMenu();
			}
			break;
		}
		case Game::ShowingSplash:
		{
			ShowSplahsScreen();
			break;
		}
		case Game::ShowingMenu:
		{
			ShowMenu();
			break;
		}
	}
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch (result)
	{
	case MainMenu::Play:
		_gameState = Game::Playing;
		break;
	case MainMenu::Exit:
		_gameState = Game::Exiting;
		break;
	}
}

void Game::ShowSplahsScreen()
{
	SplashScreen splash;
	splash.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

Game::GameState Game::_gameState = Game::Uninitialized;
sf::RenderWindow Game::_mainWindow;
PlayerPaddle Game::_paddle1;
GameObjectManager _gameObjectManager;