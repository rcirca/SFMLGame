#pragma once
#include "stdafx.h"
#include "PlayerPaddle.h"
#include "GameObjectManager.h"

class Game
{
public:
	static void Start();
	static sf::RenderWindow& getWindow();
	const static sf::Event& getEvent();
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;
	static GameObjectManager& getGameObjectManager();
	static sf::Event& getCurrentEvent();

private:
	static bool IsExiting();
	static void GameLoop();
	static void ShowSplahsScreen();
	static void ShowMenu();

	enum GameState{ Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting};


	//static sf::Event& _currentEvent;

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	static GameObjectManager _gameObjectManager;
};
