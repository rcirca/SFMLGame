#pragma once
#include "VisibleGameObject.h"


class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void add(std::string name, VisibleGameObject *gameObject);
	void remove(std::string name);
	int getObjectCount() const;
	VisibleGameObject* getGameObject(std::string name) const;
	void drawAll(sf::RenderWindow &window);
	void updateAll();

private:
	sf::Clock _clock;
	
	std::map<std::string, VisibleGameObject*> _gameObjects;
	struct GemeObjectDeallocator
	{
		void operator()(const std::pair<std::string, VisibleGameObject*> &p) const
		{
			delete p.second;
		}
	};
};