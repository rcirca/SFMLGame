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

void VisibleGameObject::update(float elapsedTime)
{
	
}

sf::Vector2f VisibleGameObject::getPosition() const
{
	if (_isLoaded)
		return _sprite.getPosition();

	return sf::Vector2f();
}

bool VisibleGameObject::isLoaded() const
{
	return _isLoaded;
}

sf::Sprite& VisibleGameObject::getSprite()
{
	return _sprite;
}

float VisibleGameObject::getHeight()
{
	return _sprite.getLocalBounds().height;
}

float VisibleGameObject::getWidth()
{
	return _sprite.getLocalBounds().width;
}

sf::Rect<float> VisibleGameObject::getBoundingRectangle() const
{
	return _sprite.getGlobalBounds();
}





