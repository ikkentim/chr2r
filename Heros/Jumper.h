#pragma once

#include "GameObject.h"
#include "Texture.h"

class Jumper : public GameObject{

public:
	Jumper(Vector2);
	void update(GameScene *, double, Keys) override;
	void render(Viewport &) override;
    void entered_collision(GameScene *, GameObject *, Vector2) override;

private:
	SpriteSheet *spriteSheet_;
	double 	animationTime_ = 0;
	int animationIndex_ = 0;
	int cooldown = 0;

};