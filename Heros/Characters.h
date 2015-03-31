/**
 * Characters.h
 * Declares a number of Character subclasses.
 */
#pragma once

#include "Character.h"

// Represents the mario tutor
class Mario : public Character {
public:
    // A constructor which sets the position
	Mario(Vector2);

    // Performs the update logic
    void update(GameScene*, double, Keys) override;

    // Renders the graphics
    void render(Viewport &vp) override;
};

// Represents the sonic tutor
class Sanic : public Character {
public:
    // A constructor which sets the position
	Sanic(Vector2);

    // Performs the update logic
    void update(GameScene*, double, Keys) override;

    // Renders the graphics
    void render(Viewport &vp) override;
};

// Represents the magicarp tutor
class Magikarp : public Character {
public:
    // A constructor which sets the position
	Magikarp(Vector2);

    // Performs the update logic
    void update(GameScene*, double, Keys) override;

    // Renders the graphics
    void render(Viewport &vp) override;

private:
	int animationIndex_ = 0;
	int animationFrames_ = 3;
	double animationTime_ = 0;
};

// Represents the snake tutor
class Snake : public Character {
public:
    // A constructor which sets the position
	Snake(Vector2);

    // Performs the update logic
    void update(GameScene*, double, Keys) override;

    // Renders the graphics
    void render(Viewport &vp) override;
};