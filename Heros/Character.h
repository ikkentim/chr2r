#pragma once
#include "Actor.h"
#include "Ability.h"
class Character : public Actor {
public:
	Character(Vector2, Vector2);
	void Update(GameScene*, double, Keys);
	virtual void Render(Viewport &vp) = 0;
	SpriteSheet *spriteSheet_;
	bool finisheddialog = false;
	Ability ability;
};

