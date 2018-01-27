#include "PlayerPaddle.h"
#include "Game.h"

PlayerPaddle::PlayerPaddle() :
_velocity(0),
_maxVelocity(300.0f)
{
	load("images/paddle.png");
	assert(isLoaded());

	getSprite().setOrigin(getSprite().getLocalBounds().width / 2, getSprite().getLocalBounds().height / 2);
}

PlayerPaddle::~PlayerPaddle()
{

}


void PlayerPaddle::update(float elapsedTime)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		_velocity -= 3.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		_velocity += 3.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		_velocity = 0.0f;

	if (_velocity > _maxVelocity)
		_velocity = _maxVelocity;

	if (_velocity < -_maxVelocity)
		_velocity = -_maxVelocity;

	auto position = this->getPosition();

	if (position.x < getSprite().getLocalBounds().width / 2)
		if (_velocity < 0)
			_velocity = 0;
	if (position.x > (Game::SCREEN_WIDTH - getSprite().getLocalBounds().width / 2))
		if (_velocity > 0)
			_velocity = 0;
	position.x = position.x + _velocity;
	getSprite().move(_velocity, 0);
	_velocity = 0;
}

void PlayerPaddle::draw(sf::RenderWindow &window)
{
	VisibleGameObject::draw(window);
}

float PlayerPaddle::getVelocity() const
{
	return _velocity;
}
