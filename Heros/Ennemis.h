#pragma once

#include <stdio.h>
#include "Actor.h"
#include "SpriteSheet.h"

class Ennemis : public Actor {
public:
	Ennemis(Vector2, SpriteSheet *);
	~Ennemis();
    void GoLeft(double);
    void GoRight(double);
	//void Render(Viewport &) override; // This class is virtual now!
	void Update(GameScene *, double, Keys) override;
	void EnteredCollision(GameScene *, GameObject *, Vector2) override;
protected:
    SpriteSheet *spriteSheet() {
        return spriteSheet_;
    }
private:
    SpriteSheet *spriteSheet_;
};