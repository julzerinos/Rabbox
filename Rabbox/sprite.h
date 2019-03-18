#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <string>

class Graphics;

class Sprite
{
public:
	Sprite();
	Sprite(Graphics& graphics, const std::string& file, int Ox, int Oy, int w, int h, float posX, float posY);
	virtual ~Sprite();
	virtual void update();
	void draw(Graphics& graphics, int x, int y);

protected:
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;
	float _x, _y;

private:
};

#endif
