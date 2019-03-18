#ifndef LEVEL_H
#define LEVEL_H

#include <string>

#include "globals.h"

class Graphics;
struct SDL_Texture;

class Level
{
public:
	Level();
	Level(Graphics & graphics, std::string map, DisplacementVector spawnPoint);
	~Level();

	void update(int elapsedTime);
	void draw(Graphics & graphics);

private:
	std::string _mapName;
	DisplacementVector _mapSize;
	
	DisplacementVector _spawnPoint;

	SDL_Texture * _bgTexture;

	void loadMap(Graphics & graphics, std::string mapName);

};

#endif
