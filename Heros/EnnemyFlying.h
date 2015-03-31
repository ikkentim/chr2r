/**
 * EnnemyFlying.h
 * Declares the EnnemyFlying class.
 */
#pragma once

#include "Ennemis.h"
#include "SpriteSheet.h"

// Represents an enemy bird
class EnnemyFlying : public Ennemis {
public:
    // Enumartion of animation states
	enum AnimationState {
		RUN_RIGHT,
		RUN_LEFT,
    };

    // A constructor which sets the position 
    EnnemyFlying(Vector2 position);

    // Default destructor
	~EnnemyFlying();

    // Move down for the specified delta time at the specified tick
    void go_down(double delta, int tick);

    // Move up for the specified delta time at the specified tick
	void go_up(double,int);

    // Performs the update logic
    void update(GameScene *, double, Keys) override;

    // Renders the graphics
    void render(Viewport &) override;


private:
	AnimationState state_;
	double animationTime_ = 0;
	int animationIndex_ = 0;
	int animationFrames_ = 1;
	int nbTick_ = 0;
	Vector2 start_position_;

    AnimationState get_animation_state(int &frames);
};
