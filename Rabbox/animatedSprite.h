#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <map>
#include <vector>
#include <string>

#include "globals.h"
#include "sprite.h"

class Graphics;

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite();
	AnimatedSprite(Graphics& graphics, const std::string & file,
		int ox, int oy, int w, int h, float xpos, float ypos,
		float duration);

	void playAnimation(std::string, bool once = false);
	
	void update(int);
	void draw(Graphics&, int, int);

protected:
	double _duration;
	bool _currentAnimationOnce;
	std::string _currentAnimation;

	virtual void setupAnim() = 0;

	void addAnimation(int frames, int x, int y, std::string name, int w, int h, DisplacementVector offset);
	void resetAnim();
	void stopAnim();
	void setVisible(bool visible);
	virtual void animDone(std::string);

private:
	std::map<std::string, std::vector<SDL_Rect>> _animations;
	std::map<std::string, DisplacementVector> _offsets;

	int _frameIndex;
	double _timeElapsed = 0.0;
	bool _visible;
};

#endif // !ANIMATED_SPRITE_H
