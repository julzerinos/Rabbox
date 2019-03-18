#include <SDL.h>
#include <SDL_image.h>

#include "graphics.h"
#include "globals.h"

Graphics::Graphics()
{
	SDL_CreateWindowAndRenderer(globals::SCREEN_W, globals::SCREEN_H, 0, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "Rabbox");
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(this->_window);
}

SDL_Surface* Graphics::loadImage(const std::string& file)
{
	if (this->_spriteSheet.count(file) == 0)
		this->_spriteSheet[file] = IMG_Load(file.c_str());
	return this->_spriteSheet[file];
}

void Graphics::blitSurface(SDL_Texture* source, SDL_Rect* sourceRect, SDL_Rect* destRect)
{
	SDL_RenderCopy(this->_renderer, source, sourceRect, destRect);
}

void Graphics::flip()
{
	SDL_RenderPresent(this->_renderer);
}

void Graphics::clear()
{
	SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const 
{
	return this->_renderer;
}