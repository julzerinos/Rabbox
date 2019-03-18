#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "animatedSprite.h"
#include "globals.h"

namespace player_const
{
	const float MOVE_SPEED = 2.0f;
}

class Graphics;

class Player : public AnimatedSprite
{
public:
	Player();
	Player(Graphics & graphics, float x, float y);
	void draw(Graphics & graphics);
	void update(float elapsedTime);

	void moveLeft();
	void moveRight();
	void stopMoving();

	virtual void animDone(std::string curr);
	virtual void setupAnim();

private:
	bool _isSliding = true;
	bool _stoppedMoving = true;
	float _dx = 0, _dy;
	Direction _facing = RIGHT;
};

#endif
