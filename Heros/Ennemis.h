#pragma once

#include <stdio.h>
#include "Actor.h"
#include "SpriteSheet.h"

class Ennemis : public Actor {
public:
	Ennemis(Vector2, SpriteSheet *);
	~Ennemis();
    void go_left(double);
    void go_right(double);
	void update(GameScene *, double, Keys) override;
	void entered_collision(GameScene *, GameObject *, Vector2) override;
	bool is_dead_state(State);
protected:
    SpriteSheet *spriteSheet() {
        return spriteSheet_;
    }
private:
    SpriteSheet *spriteSheet_;
};