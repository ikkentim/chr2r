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