#pragma once

namespace globals
{
	const int SCREEN_W = 1366;
	const int SCREEN_H = 768;

	const float SPRITE_SCALE = 1;
}

enum Direction
{
	LEFT,
	RIGHT,
};


struct DisplacementVector
{
	int x, y;
	DisplacementVector() : x(0), y(0) {}
	DisplacementVector(int x, int y) : x(x), y(y) {}
	DisplacementVector zero()
	{
		return DisplacementVector(0, 0);
	}
};