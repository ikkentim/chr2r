#pragma once

#include "Actor.h"
#include "Keys.h"
#include <irrKlang.h>

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
        SLIDE_RIGHT,
        SLIDE_LEFT,
		IDLE
	};

    Player(class GameScene *, Vector2 position, Vector2 size);
    void Update(double, Keys) override;
    void Render(Viewport &) override;

private:
    Keys keys_ = KEY_NONE;
    bool isDucking_ = false;
	double animationTime_ = 0;
	int animationIndex_ = 0;
    int animationFrames_ = 1;
    AnimationState state_;
    irrklang::ISoundEngine *soundEngine_;

    AnimationState GetAnimationState(int &frames);
};