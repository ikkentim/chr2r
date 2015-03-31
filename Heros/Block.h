/**
 * Block.h
 * Declares the Block class.
 */
#pragma once

#include "GameObject.h"
#include "Texture.h"

// Represents a visible block
class Block : public GameObject {
public:
    // A constructor which sets the spritesheet and texture
    Block(SpriteSheet *spriteSheet, Texture texture);

    // A constructor which sets the spritesheet, texture and position
    Block(SpriteSheet *spriteSheet, Texture texture, Vector2 position);

    // Performs a logical update
    void update(GameScene *, double, Keys) override;

    // Renders the graphics
    void render(Viewport &) override;
private:
    SpriteSheet *spriteSheet_;
    Texture texture_;
};