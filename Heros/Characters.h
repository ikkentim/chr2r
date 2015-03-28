#pragma once
#include "Character.h"
class Mario : public Character {
public:
	Mario(Vector2);

    void update(GameScene*, double, Keys) override;
    void render(Viewport &vp) override;
};

class Sanic : public Character {
public:
	Sanic(Vector2);

	void update(GameScene*, double, Keys);
	void render(Viewport &vp);
};

class Magikarp : public Character {
public:
	Magikarp(Vector2);

	void update(GameScene*, double, Keys);
	void render(Viewport &vp);

private:
	int animationIndex_ = 0;
	int animationFrames_ = 3;
	double animationTime_ = 0;
	int texture_top = 36;
	int texture_left = 30;
};