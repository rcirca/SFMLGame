#include "VisibleGameObject.h"



VisibleGameObject::VisibleGameObject()
{
	_isLoaded = false;
}

VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::load(std::string fileName)
{
	if (_texture.loadFromFile(fileName) == false)
	{
		_fileName = "";
		_isLoaded = false;
	}
	else
	{
		_fileName = fileName;
		_sprite.setTexture(_texture);
		_isLoaded = true;
	}
}

void VisibleGameObject::draw(sf::RenderWindow &window)
{
	if (_isLoaded)
		window.draw(_sprite);
}

void VisibleGameObject::setPosition(float x, float y)
{
	if (_isLoaded) 
	{
		_sprite.setPosition(x, y);
	}
}