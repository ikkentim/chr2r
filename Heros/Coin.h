#pragma once

#include "GameObject.h"
#include "Texture.h"

class Coin : public GameObject{
public:
	Coin(Texture);
	Coin(Texture, Vector2);
	void Update(double, Keys) override;
	void Render(Viewport &) override;
private:
	Texture texture_;
};