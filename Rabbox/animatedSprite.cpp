#include "animatedSprite.h"
#include "graphics.h"

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(Graphics& graphics, const std::string & file,
	int ox, int oy, int w, int h, float xpos, float ypos,
	float duration) : Sprite(graphics, file, ox, oy, w, h, xpos, ypos),
	_frameIndex(0),
	_duration(duration),
	_visible(true),
	_currentAnimationOnce(false),
	_currentAnimation("")
{}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int w, int h, DisplacementVector offset)
{
	std::vector<SDL_Rect> rects;
	for (int i = 0; i < frames; i++)
	{
		SDL_Rect newRect = { (i + x) * w, y, w, h };
		rects.push_back(newRect);
	}
	this->_animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, rects));
	this->_offsets.insert(std::pair<std::string, DisplacementVector>(name, offset));
}

void AnimatedSprite::resetAnim()
{
	this->_animations.clear();
	this->_offsets.clear();
}

void AnimatedSprite::playAnimation(std::string anim, bool once)
{
	this->_currentAnimationOnce = once;
	if (this->_currentAnimation != anim)
	{
		this->_currentAnimation = anim;
		this->_frameIndex = 0;
	}
}

void AnimatedSprite::setVisible(bool vis)
{
	this->_visible = vis;
}

void AnimatedSprite::stopAnim()
{
	this->_frameIndex = 0;
	this->animDone(this->_currentAnimation);
}

void AnimatedSprite::update(int elapsedTime)
{
	Sprite::update();

	this->_timeElapsed += elapsedTime;
	if (this->_timeElapsed > this->_duration)
	{
		this->_timeElapsed -= this->_duration;
		if (this->_frameIndex < this->_animations[this->_currentAnimation].size() - 1)
			this->_frameIndex++;
		else
		{
			if (this->_currentAnimationOnce == true)
				this->setVisible(false);
			this->_frameIndex = 0;
			this->animDone(this->_currentAnimation);
		}
	}
}

void AnimatedSprite::draw(Graphics& graphics, int x, int y)
{
	if (this->_visible)
	{
		SDL_Rect destRect;
		destRect.x = x + this->_offsets[this->_currentAnimation].x;
		destRect.y = y + this->_offsets[this->_currentAnimation].y;
		destRect.w = this->_sourceRect.w *globals::SPRITE_SCALE;
		destRect.h = this->_sourceRect.h *globals::SPRITE_SCALE;

		SDL_Rect sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];
		graphics.blitSurface(this->_spriteSheet, &sourceRect, &destRect);
	}
}

void AnimatedSprite::animDone(std::string curr)
{

}

void AnimatedSprite::setupAnim()
{
	this->addAnimation(12, 0, 0, "moveRight", 64, 64, DisplacementVector(0, 0));
	this->addAnimation(12, 0, 64, "moveLeft", 64, 64, DisplacementVector(0, 0));
}