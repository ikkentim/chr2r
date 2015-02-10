#pragma once

#include <stdio.h>
#include "Actor.h"
#include "SpriteSheet.h"

class Ennemis : public Actor {
public:
	Ennemis(Vector2, Vector2);
	~Ennemis();
    void GoLeft(double);
    void GoRight(double);
	void Render(Viewport &) override;
    void Update(double, Keys) override;
};