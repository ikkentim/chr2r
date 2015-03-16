#pragma once
#include "Character.h"
class Mario : public Character {
public:
	void Update(GameScene*, double, Keys);
	void Render(Viewport &vp);
	Mario(Vector2);
};

class Sanic : public Character {
public:
	void Update(GameScene*, double, Keys);
	void Render(Viewport &vp);
	Sanic(Vector2);
};

class Magikarp : public Character {
public:
	void Update(GameScene*, double, Keys);
	void Render(Viewport &vp);
	Magikarp(Vector2);

private:
	int animationIndex_ = 0;
	int animationFrames_ = 3;
	double animationTime_ = 0;
	int texture_top = 36;
	int texture_left = 30;
};