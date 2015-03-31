/**
 * EnnemyJumping.h
 * Declares the EnnemyJumping class.
 */
#pragma once

#include "Ennemis.h"
#include "SpriteSheet.h"

// Represents an enemy jumper
class EnnemyJumping : public Ennemis {
public:
    // Enumartion of animation states
	enum AnimationState {
		RUN_RIGHT,
		RUN_LEFT,
		JUMP_
    };

    // A constructor which sets the position 
    EnnemyJumping(Vector2 position);

    // Default destructor
	~EnnemyJumping();

    // Jump up
    void jump(double);

    // Performs the update logic
    void update(GameScene *, double, Keys) override;

    // Renders the graphics
    void render(Viewport &) override;

private:
	AnimationState state_;
	double animationTime_ = 0;
	int animationIndex_ = 0;
	int animationFrames_ = 1;

	AnimationState get_animation_state(int &frames);
};
