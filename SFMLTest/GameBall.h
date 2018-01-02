#pragma once
#include "VisibleGameObject.h"

class GameBall: public VisibleGameObject
{
public:
	GameBall();
	virtual ~GameBall();
	void update(float);

private:
	float _velocity;
	float _angle;
	float _elapsedTimeSinceStart;

	float LinearVelocityX(float angle) const;
	float LinearVelocityY(float angle) const;
};