#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "GameBall.h"

void Game::Start()
{
	if (_gameState != Game::Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Pang!");
	PlayerPaddle *player1 = new PlayerPaddle();
	player1->setPosition((SCREEN_WIDTH / 2), 700);

	GameBall *ball = new GameBall();
	ball->setPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - 15);

	_gameObjectManager.add("Paddle1", player1);
	_gameObjectManager.add("Ball", ball);

	_gameState = Game::ShowingSplash;

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
	sf::Event _currentEvent;
	_mainWindow.pollEvent(_currentEvent);

	switch (_gameState)
	{
		case Game::Playing:
		{
			_mainWindow.clear(sf::Color(0, 0, 0));

			_gameObjectManager.updateAll();
			_gameObjectManager.drawAll(_mainWindow);

			_mainWindow.display();

			if (_currentEvent.type == sf::Event::Closed)
				_gameState = Game::Exiting;
			if (_currentEvent.type == sf::Event::LostFocus)
				ShowMenu();
			if (_currentEvent.type == sf::Event::KeyPressed)
				if (_currentEvent.key.code == sf::Keyboard::Escape)
					ShowMenu();
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
		default:
			break;
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

sf::RenderWindow& Game::getWindow()
{
	return _mainWindow;
}

GameObjectManager& Game::getGameObjectManager()
{
	return _gameObjectManager;
}


const sf::Event& Game::getEvent()
{
	sf::Event currentEvent;
	if(_mainWindow.pollEvent(currentEvent))
		return currentEvent;
	return {};
}

//sf::Event& Game::getCurrentEvent()
//{
//	return {};
//}




Game::GameState Game::_gameState = Game::Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
