#include "GameBall.h"
#include <random>
#include "Game.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <chrono>

GameBall::GameBall() :
_velocity((300.0f)),
_elapsedTimeSinceStart(0.0f)
{
	load("images/ball.png");
	assert(isLoaded());

	getSprite().setOrigin(15, 15);

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, 360);
	_angle = distribution(generator);
}


GameBall::~GameBall()
{
	
}

void GameBall::update(float elapsedTime)
{
	_elapsedTimeSinceStart += elapsedTime;

	if (_elapsedTimeSinceStart < 3.0f)
		return;

	auto moveAmount = _velocity * elapsedTime;

	auto moveByX = LinearVelocityX(_angle) * moveAmount;
	auto moveByY = LinearVelocityY(_angle) * moveAmount;

	//collide with left side of screen
	if (getPosition().x + moveByX <= 0 + getWidth() / 2
		|| getPosition().x + getHeight() / 2 + moveByX >= Game::SCREEN_WIDTH)
	{
		//bounce off of
		_angle = 360.0f - _angle;
		if (_angle > 260.0f && _angle < 280.0f)
			_angle += 20.0f;
		if (_angle > 80.0f && _angle < 100.0f)
			_angle += 20.0f;
		moveByX = -moveByX;
	}

	PlayerPaddle* player1 = dynamic_cast<PlayerPaddle*>(Game::getGameObjectManager().getGameObject("Paddle1"));
	
	if (player1 == NULL)
		return;

	auto player1BB = player1->getBoundingRectangle();

	if (player1BB.intersects(getBoundingRectangle()))
	{
		_angle = 360.0f - (_angle - 180.0f);
		if (_angle > 360.0f)
			_angle -= 360.0f;

		moveByY = -moveByY;

		//check if ball is inside
		//todo make a funciton for that specifically to make it more readable
		if (getBoundingRectangle().top + getBoundingRectangle().height > player1->getBoundingRectangle().top)
		{
			std::cout << "Ball inside paddle" << std::endl;
			setPosition(getPosition().x, player1->getBoundingRectangle().top - getWidth() / 2 - 1);
		}

		auto playerVelocity = player1->getVelocity();

		if (playerVelocity < 0)
		{
			_angle -= 20.0f;

			if (_angle < 0)
				_angle = 360.0f - _angle;
		}
		else if (playerVelocity > 0)
		{
			_angle += 20.0f;

			if (_angle > 360.0f)
				_angle = _angle - 360.0f;
		}

		_velocity += 0.01f;
		std::cout << "_velocity: " << _velocity << std::endl;
	}

	if (getPosition().y - getHeight() / 2 <= 0)
	{
		_angle = 180 - _angle;
		moveByY = -moveByY;
	}

	if (getPosition().y + getHeight() / 2 + moveByY >= Game::SCREEN_HEIGHT)
	{
		//temp move to middle of screen and randomize angle
		getSprite().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
		std::default_random_engine generator;
		generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<int> distribution(0, 360);
		_angle = distribution(generator);
		_velocity = 300.0f;
		_elapsedTimeSinceStart = 0.0f;
	}

	getSprite().move(moveByX, moveByY);

}

float GameBall::LinearVelocityX(float angle) const
{
	angle -= 90;

	if (angle < 0)
		angle = 360 + angle;

	return std::cos(angle * (M_PI / 180.0f));
}


float GameBall::LinearVelocityY(float angle) const
{
	angle -= 90;

	if (angle < 0)
		angle = 360 + angle;

	return std::sin(angle * (M_PI / 180.0f));
}


