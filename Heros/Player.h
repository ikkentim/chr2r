#pragma once

#include "Actor.h"

class Player : public Actor {
public:
    enum AnimationState{
		RUN_RIGHT = 0,
		RUN_LEFT,
		JUMP_RIGHT,
		JUMP_LEFT,
		FALL_RIGHT,
		FALL_LEFT,
        DUCK_RIGHT,
        DUCK_LEFT,
		IDLE
	};

    Player(Vector2 position, Vector2 size);
    void Update(double, Keys) override;
    void Render(Viewport &) override;
private:
    bool isDucking_ = false;
	double animationTime_ = 0;
	int animationIndex_ = 0;
    int animationFrames_ = 1;
    AnimationState state_;

    AnimationState GetAnimationState(int &frames);

};