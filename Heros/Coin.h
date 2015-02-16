#pragma once

#include "GameObject.h"

class Coin : public GameObject{
public:
	Coin(Vector2);
    void Update(GameScene *, double, Keys) override;
	void Render(Viewport &) override;
    void EnteredCollision(GameScene *, GameObject *, Vector2) override;
private:
    double 	animationTime_ = 0;
    int animationIndex_ = 0;
};