#pragma once

#include "GameObject.h"
#include "Texture.h"

class Jumper : public GameObject{

public:
	Jumper(Vector2);
	void Update(GameScene *, double, Keys) override;
	void Render(Viewport &) override;
	void EnteredCollision(GameScene *, GameObject *, Vector2) override;

private:
	SpriteSheet *spriteSheet_;
	double 	animationTime_ = 0;
	int animationIndex_ = 0;
	int cooldown = 0;

};