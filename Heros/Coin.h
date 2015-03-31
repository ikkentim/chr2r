/**
 * Coin.h
 * Declares the Coin class.
 */
#pragma once

#include "GameObject.h"

// Represens a coin
class Coin : public GameObject{
public:
    // A constructor which sets the position
    Coin(Vector2  position);

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
    bool pickedUp_ = false;
};