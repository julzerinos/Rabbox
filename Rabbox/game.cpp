#include <SDL.h>
#include <SDL_mixer.h>

#include <algorithm>

#include "game.h"
#include "graphics.h"
#include "input.h"
#include "player.h"

namespace
{
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game()
{

}

void Game::gameLoop()
{
	Graphics graphics;
	Input input;
	SDL_Event event;

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_Music * bgMusic = NULL;
	if ((bgMusic = Mix_LoadMUS("content/sound/music/test_mus.wav")) == NULL)
		return;

	bool memeToggled = false;
	Mix_Chunk * gottagofast = NULL;
	if ((gottagofast = Mix_LoadWAV("content/sound/effects/gottagofast.wav")) == NULL)
		return;

	Mix_PlayMusic(bgMusic, -1);

	this->_player = Player(graphics, -75, 460);
	this->_level = Level(graphics, "test_map", DisplacementVector(100, 100));

	int LAST_UPDATE_TIME = SDL_GetTicks();
	while (true)
	{
		input.beginNewFrame();

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.repeat == 0)
					input.keyDownEvent(event);
			}
			else if (event.type == SDL_KEYUP)
			{
				if (event.key.repeat == 0)
					input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT)
				return;
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true)
		{
			Mix_FreeChunk(gottagofast);
			Mix_FreeMusic(bgMusic);
			Mix_CloseAudio();
			SDL_Quit();
			break;
		}
		else if (input.isKeyHeld(SDL_SCANCODE_LEFT) == true)
		{
			if (memeToggled)
				Mix_PlayChannel(-1, gottagofast, 0);

			this->_player.moveLeft();
			for (auto & rabbit : shitsandgiggles)
				rabbit.moveRight();
		}
		else if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true)
		{
			if (memeToggled)
				Mix_PlayChannel(-1, gottagofast, 0);

			this->_player.moveRight();
			for (auto & rabbit : shitsandgiggles)
				rabbit.moveLeft();
		}
		if (!input.isKeyHeld(SDL_SCANCODE_RIGHT) && !input.isKeyHeld(SDL_SCANCODE_LEFT))
		{
			if (memeToggled)
				Mix_HaltChannel(-1);

			this->_player.stopMoving();
			for (auto & rabbit : shitsandgiggles)
				rabbit.stopMoving();
		}
		if (input.wasKeyPressed(SDL_SCANCODE_SPACE))
		{
			shitsandgiggles.push_back(Player(graphics, rand() % 1367, rand() % 769));
		}
		if (input.wasKeyPressed(SDL_SCANCODE_M))
		{
			memeToggled = memeToggled ? false : true;
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		const int ELAPSED = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		this->update(std::min(ELAPSED, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphics);
	}
}

void Game::draw(Graphics& graphics)
{
	graphics.clear();

	this->_level.draw(graphics);
	this->_player.draw(graphics);
	for (auto & rabbit : shitsandgiggles)
		rabbit.draw(graphics);
	graphics.flip();
}

void Game::update(float elapsedTime)
{
	this->_player.update(elapsedTime);
	for (auto & rabbit : shitsandgiggles)
		rabbit.update(elapsedTime);
	this->_level.update(elapsedTime);
}

