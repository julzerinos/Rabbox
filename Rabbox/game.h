#ifndef GAME_H
#define GAME_H

#include "animatedSprite.h"
#include "player.h"
#include "level.h"

class Graphics;

class Game
{
public:
	Game();
	~Game();
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	Player _player;
	std::vector<Player> shitsandgiggles;
	Level _level;
};

#endif
