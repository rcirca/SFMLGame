#include "GameObjectManager.h"
#include "Game.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GemeObjectDeallocator());
}

void GameObjectManager::add(std::string name, VisibleGameObject *gameObject)
{
	_gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

void GameObjectManager::remove(std::string name)
{
	std::map<std::string, VisibleGameObject*>::iterator results = _gameObjects.find(name);
	if (results != _gameObjects.end())
	{
		delete results->second;
		_gameObjects.erase(name);
	}
}

int GameObjectManager::getObjectCount() const
{
	return _gameObjects.size();
}

VisibleGameObject* GameObjectManager::getGameObject(std::string name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
	if (results == _gameObjects.end())
		return NULL;

	return results->second;
}

void GameObjectManager::drawAll(sf::RenderWindow &window)
{
	std::map<std::string, VisibleGameObject*>::iterator gameObjIter = _gameObjects.begin();
	while (gameObjIter != _gameObjects.end())
	{
		gameObjIter->second->draw(window);
		gameObjIter++;
	}
}

void GameObjectManager::updateAll()
{
	std::map<std::string, VisibleGameObject*>::const_iterator iterator = _gameObjects.begin();

	float timeDelta = _clock.restart().asSeconds();

	while(iterator != _gameObjects.end())
	{
		iterator->second->update(timeDelta);
		iterator++;
	}
}

