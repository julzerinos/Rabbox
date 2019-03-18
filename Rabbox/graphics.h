#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <map>

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
	Graphics();
	~Graphics();

	SDL_Surface* loadImage(const std::string &file);

	void blitSurface(SDL_Texture* source, SDL_Rect* sourceRect, SDL_Rect* destRect);
	void flip();
	void clear();
	SDL_Renderer* getRenderer() const;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::map<std::string, SDL_Surface*> _spriteSheet;
};

#endif

