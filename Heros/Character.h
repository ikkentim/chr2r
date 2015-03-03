#pragma once
#include "Actor.h"

class Character : public Actor {
public:
	Character();
	void Update(GameScene*, double, Keys);
	void Render(Viewport &vp);
};