#include "player.h"
#include "graphics.h"

Player::Player() {}

Player::Player(Graphics & graphics, float x, float y)
	: AnimatedSprite(graphics, "content/sprites/playerRabbit.png", 0, 0, 64, 64, x, y, 130)
{
	graphics.loadImage("playerRabbit.png");

	this->setupAnim();
	this->playAnimation("idleRight");
}

void Player::setupAnim()
{
	this->addAnimation(2, 0, 0, "idleRight", 64, 64, DisplacementVector(0, 0));
	this->addAnimation(12, 0, 0, "moveRight", 64, 64, DisplacementVector(0, 0));
	this->addAnimation(2, 0, 64, "idleLeft", 64, 64, DisplacementVector(0, 0));
	this->addAnimation(12, 0, 64, "moveLeft", 64, 64, DisplacementVector(0, 0));
}

void Player::animDone(std::string curr) {}

void Player::update(float elapsedTime)
{
	this->_x += this->_dx * elapsedTime;

	AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics & graphics)
{
	AnimatedSprite::draw(graphics, this->_x, this->_y);
}

void Player::moveLeft()
{
	this->_dx = -player_const::MOVE_SPEED;
	this->playAnimation("moveLeft");
	this->_facing = LEFT;
}

void Player::moveRight()
{
	this->_dx = player_const::MOVE_SPEED;
	this->playAnimation("moveRight");
	this->_facing = RIGHT;
}

void Player::stopMoving()
{
	if (this->_isSliding)
		this->_dx = this->_dx * 0.997f;
	else
		this->_dx = 0.0f;

	this->playAnimation(this->_facing == RIGHT ? "idleRight" : "idleLeft");
}