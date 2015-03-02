#pragma once

#include <stdio.h>
#include "Ennemis.h"
#include "SpriteSheet.h"

class EnnemyFlying : public Ennemis {
public:
	enum AnimationState{
		RUN_RIGHT,
		RUN_LEFT,
	};
	EnnemyFlying(Vector2);
	~EnnemyFlying();

	void GoLeft(double,int);
	void GoRight(double,int);

	void Render(Viewport &) override;
	void Update(GameScene *, double, Keys) override;

protected: //private ?
	AnimationState state_;
	double animationTime_ = 0;
	int animationIndex_ = 0;
	int animationFrames_ = 1;
	int nbTick_ = 0;

	AnimationState GetAnimationState(int &frames);
};
