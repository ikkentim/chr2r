/**
 * EnnemyDog.h
 * Declares the EnnemyDog class.
 */
#pragma once

#include "Ennemis.h"
#include "SpriteSheet.h"

// Represents an enemy dog
class EnnemyDog : public Ennemis{
public:
    // Enumartion of animation states
	enum AnimationState {
		RUN_RIGHT,
		RUN_LEFT
    };

    // A constructor which sets the position 
    EnnemyDog(Vector2 position);

    // Default destructor
    ~EnnemyDog();

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