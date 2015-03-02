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

	void Render(Viewport &) override;
	void Update(GameScene *, double, Keys) override;

protected: //private ?
	AnimationState state_;
	double animationTime_ = 0;
	int animationIndex_ = 0;
	int animationFrames_ = 1;

	AnimationState GetAnimationState(int &frames);
};
