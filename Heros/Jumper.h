/**
 * Jumper.h
 * Declares the Jumper class.
 */
#pragma once

#include "GameObject.h"
#include "Texture.h"

// Represents a trampoline
class Jumper : public GameObject{

public:
    // A constructor which sets the position
    Jumper(Vector2 position);

    // Performs the update logic
    void update(GameScene *, double, Keys) override;

    // Renders the graphics
    void render(Viewport &) override;

    // Contains logic for handling collisions
    virtual void entered_collision(GameScene *scene, GameObject *other,
        Vector2 overlap);

private:
	SpriteSheet *spriteSheet_;
	double 	animationTime_ = 0;
	int animationIndex_ = 0;
	int cooldown = 0;

};