/**
 * Ennemis.h
 * Declares the abstract Ennemis class.
 */
#pragma once

#include <stdio.h>
#include "Actor.h"
#include "SpriteSheet.h"

// Contains method declarations and methods for an enemy
class Ennemis : public Actor {
public:
    // A constructor which sets the position and sprite sheet
	Ennemis(Vector2 position, SpriteSheet *spriteSheet);

    // Default destructor
    virtual ~Ennemis() {};

    // Move to the left for the specified delta time
    void go_left(double);

    // Move to the right for the specified delta time
    void go_right(double);

    // Performs the update logic
    void update(GameScene *, double, Keys) override;

    // Contains logic for handling collisions
	void entered_collision(GameScene *scene, GameObject *other, 
        Vector2 overlap) override;
protected:
    // Gets the sprite sheet
    SpriteSheet *sprite_sheet() {
        return spriteSheet_;
    }
private:
    SpriteSheet *spriteSheet_;
};