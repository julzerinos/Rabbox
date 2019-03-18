#include <SDL.h>

#include "level.h"
#include "graphics.h"

Level::Level() {}

Level::Level(Graphics & graphics, std::string map, DisplacementVector spawnPoint)
	: _mapName(map), _spawnPoint(spawnPoint), _mapSize(_mapSize.zero())
{
	this->loadMap(graphics, map);
}

Level::~Level()
{
}

void Level::update(int elapsedTime)
{

}

void Level::draw(Graphics & graphics)
{
	SDL_Rect sourceRect = { 0, 0, 1366, 768 };
	SDL_Rect destRect = { 0, 0, 1366, 768 };
	graphics.blitSurface(this->_bgTexture, &sourceRect, &destRect);

}

void Level::loadMap(Graphics & graphics, std::string mapName)
{
	this->_bgTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/bg/bg_test.png"));
	if (this->_bgTexture == NULL)
		printf("SDL_CreateTextureFromSurface failed during background creation: %s", SDL_GetError());
	this->_mapSize = DisplacementVector(1366, 768);
}

