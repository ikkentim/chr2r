#pragma once

#include <stdio.h>
#include "Ennemis.h"
#include "SpriteSheet.h"

class EnnemyJumping : public Ennemis {
public:
	enum AnimationState{
		RUN_RIGHT,
		RUN_LEFT,
		JUMP_
	};
	EnnemyJumping(Vector2);
	~EnnemyJumping();

	void Jump(double);

	void render(Viewport &) override;
	void update(GameScene *, double, Keys) override;

private:
	AnimationState state_;
	double animationTime_ = 0;
	int animationIndex_ = 0;
	int animationFrames_ = 1;

	AnimationState get_animation_state(int &frames);
};
