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

	void go_down(double,int); //Go down
	void go_up(double,int);// Go Up

	void render(Viewport &) override;
	void update(GameScene *, double, Keys) override;


private:
	AnimationState state_;
	double animationTime_ = 0;
	int animationIndex_ = 0;
	int animationFrames_ = 1;
	int nbTick_ = 0;
	Vector2 start_position;

    AnimationState get_animation_state(int &frames);
};
