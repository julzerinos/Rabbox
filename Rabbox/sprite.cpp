#include "sprite.h"
#include "graphics.h"
#include "globals.h"

Sprite::Sprite() {}

Sprite::Sprite(
	Graphics& graphics,
	const std::string & file,
	int Ox, int Oy, int w, int h,
	float posX, float posY)
	: _x(posX), _y(posY)
{
	this->_sourceRect.x = Ox;
	this->_sourceRect.y = Oy;
	this->_sourceRect.w = w;
	this->_sourceRect.h = h;

	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(file));
	if (this->_spriteSheet == NULL) 
		printf("SDL_CreateTextureFromSurface failed during sprite creation: %s", SDL_GetError());
}

Sprite::~Sprite()
{
}

void Sprite::draw(Graphics& graphics, int x, int y)
{
	SDL_Rect destRect = { x, y, this->_sourceRect.w * globals::SPRITE_SCALE, this->_sourceRect.h * globals::SPRITE_SCALE };
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destRect);
}

void Sprite::update() {}
