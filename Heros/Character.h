#pragma once
#include "Actor.h"

class Character : public Actor {
public:
	Character(Vector2);
	void Update(GameScene*, double, Keys);
	void Render(Viewport &vp);
private:
    SpriteSheet *spriteSheet_;
};