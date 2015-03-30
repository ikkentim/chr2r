#pragma once

#include "GameObject.h"

class Coin : public GameObject{
public:
	Coin(Vector2);
    void update(GameScene *, double, Keys) override;
	void render(Viewport &) override;
    void entered_collision(GameScene *, GameObject *, Vector2) override;
private:
    SpriteSheet *spriteSheet_;
    double 	animationTime_ = 0;
    int animationIndex_ = 0;
    bool pickedUp_ = false;
};