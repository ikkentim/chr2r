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

	void GoDown(double,int); //Go down
	void GoUp(double,int);// Go Up

	void Render(Viewport &) override;
	void Update(GameScene *, double, Keys) override;


protected: //private ?
	AnimationState state_;
	double animationTime_ = 0;
	int animationIndex_ = 0;
	int animationFrames_ = 1;
	int nbTick_ = 0;
	Vector2 start_position;

	AnimationState GetAnimationState(int &frames);
};
